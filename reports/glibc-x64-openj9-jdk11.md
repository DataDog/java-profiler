---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:39:28 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 53-69 cores)</summary>

```
1795196092 69
1795196097 69
1795196102 69
1795196107 69
1795196112 69
1795196117 69
1795196122 69
1795196127 53
1795196132 53
1795196137 53
1795196142 53
1795196147 53
1795196152 62
1795196157 62
1795196162 62
1795196167 62
1795196172 62
1795196177 62
1795196182 62
1795196187 62
```
</details>

---

