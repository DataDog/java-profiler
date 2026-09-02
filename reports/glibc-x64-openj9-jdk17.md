---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1788369981 81
1788369986 81
1788369991 81
1788369996 81
1788370001 81
1788370006 81
1788370011 81
1788370016 81
1788370021 81
1788370026 81
1788370031 81
1788370036 81
1788370041 81
1788370046 81
1788370051 81
1788370056 81
1788370061 77
1788370066 77
1788370071 77
1788370076 77
```
</details>

---

