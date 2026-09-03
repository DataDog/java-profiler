---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 15:56:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 59-66 cores)</summary>

```
1788465048 59
1788465053 59
1788465058 59
1788465063 59
1788465068 59
1788465073 59
1788465078 59
1788465083 64
1788465088 64
1788465093 64
1788465098 64
1788465103 64
1788465108 64
1788465113 66
1788465118 66
1788465123 66
1788465128 66
1788465133 66
1788465138 66
1788465143 64
```
</details>

---

