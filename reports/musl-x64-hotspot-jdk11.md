---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:37:26 EST

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
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 76-87 cores)</summary>

```
1795613514 76
1795613519 76
1795613524 78
1795613529 78
1795613534 78
1795613539 78
1795613544 78
1795613549 78
1795613554 87
1795613559 87
1795613564 87
1795613569 87
1795613574 87
1795613579 87
1795613584 87
1795613589 87
1795613594 87
1795613599 87
1795613604 87
1795613609 87
```
</details>

---

