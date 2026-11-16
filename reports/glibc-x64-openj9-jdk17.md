---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:44:06 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1794836352 77
1794836357 77
1794836362 79
1794836367 79
1794836372 79
1794836377 79
1794836382 79
1794836387 79
1794836392 79
1794836397 79
1794836402 79
1794836407 79
1794836412 79
1794836417 79
1794836422 79
1794836427 79
1794836432 79
1794836437 81
1794836442 81
1794836447 72
```
</details>

---

