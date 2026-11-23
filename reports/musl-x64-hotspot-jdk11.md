---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 9 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (4 unique values: 70-79 cores)</summary>

```
1795449474 76
1795449479 76
1795449484 76
1795449489 70
1795449494 70
1795449499 70
1795449504 70
1795449509 70
1795449514 70
1795449519 70
1795449524 70
1795449529 70
1795449534 70
1795449539 70
1795449544 70
1795449549 70
1795449554 70
1795449559 70
1795449564 79
1795449569 79
```
</details>

---

