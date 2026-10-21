---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 12:26:44 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 47-70 cores)</summary>

```
1792599595 47
1792599600 49
1792599605 49
1792599610 49
1792599615 68
1792599620 68
1792599625 70
1792599630 70
1792599635 70
1792599640 70
1792599645 70
1792599650 70
1792599655 70
1792599660 70
1792599665 70
1792599670 68
1792599675 68
1792599680 68
1792599685 68
1792599690 68
```
</details>

---

