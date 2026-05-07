---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:58:44 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 54-67 cores)</summary>

```
1778165576 63
1778165581 63
1778165586 63
1778165591 63
1778165596 63
1778165601 63
1778165606 63
1778165611 63
1778165616 67
1778165622 67
1778165627 67
1778165632 62
1778165637 62
1778165642 59
1778165647 59
1778165652 59
1778165657 59
1778165662 59
1778165667 59
1778165672 59
```
</details>

---

