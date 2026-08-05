---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1785932414 94
1785932419 94
1785932424 94
1785932429 94
1785932434 94
1785932439 94
1785932444 92
1785932449 92
1785932454 92
1785932459 92
1785932464 92
1785932469 90
1785932474 90
1785932479 82
1785932484 82
1785932489 82
1785932494 82
1785932499 82
1785932504 82
1785932509 82
```
</details>

---

