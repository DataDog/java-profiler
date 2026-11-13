---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:01:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 59-84 cores)</summary>

```
1794585394 71
1794585399 71
1794585404 71
1794585409 71
1794585414 71
1794585419 71
1794585424 71
1794585429 71
1794585434 71
1794585439 71
1794585444 71
1794585449 71
1794585454 71
1794585459 59
1794585464 59
1794585469 84
1794585474 84
1794585479 62
1794585484 62
1794585489 62
```
</details>

---

