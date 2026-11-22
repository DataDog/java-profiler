---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 00:01:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 66-96 cores)</summary>

```
1795323397 79
1795323402 79
1795323407 79
1795323412 79
1795323417 79
1795323422 79
1795323427 79
1795323432 79
1795323437 79
1795323442 79
1795323447 79
1795323452 96
1795323457 96
1795323462 96
1795323467 96
1795323472 96
1795323477 96
1795323482 66
1795323487 66
1795323492 66
```
</details>

---

