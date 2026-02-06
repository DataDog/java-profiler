---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 05:14:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 12 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 81-96 cores)</summary>

```
1770372566 81
1770372571 81
1770372576 81
1770372581 81
1770372586 81
1770372591 81
1770372596 81
1770372601 96
1770372606 96
1770372611 96
1770372616 96
1770372621 96
1770372626 96
1770372631 96
1770372636 96
1770372641 96
1770372646 96
1770372651 96
1770372656 96
1770372661 96
```
</details>

---

