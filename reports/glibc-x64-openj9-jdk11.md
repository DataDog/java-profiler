---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 11:49:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 894 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 73-83 cores)</summary>

```
1791215068 83
1791215073 83
1791215078 73
1791215083 73
1791215088 73
1791215093 73
1791215098 73
1791215103 73
1791215108 73
1791215113 73
1791215118 73
1791215123 73
1791215128 75
1791215133 75
1791215138 75
1791215143 75
1791215149 75
1791215154 75
1791215159 75
1791215164 75
```
</details>

---

