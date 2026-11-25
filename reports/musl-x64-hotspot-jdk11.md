---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:39:36 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (4 unique values: 64-73 cores)</summary>

```
1795606494 69
1795606499 69
1795606504 71
1795606509 71
1795606514 71
1795606519 71
1795606524 71
1795606529 71
1795606534 71
1795606539 71
1795606544 71
1795606549 71
1795606554 71
1795606559 71
1795606564 71
1795606569 71
1795606574 71
1795606579 71
1795606584 71
1795606589 71
```
</details>

---

