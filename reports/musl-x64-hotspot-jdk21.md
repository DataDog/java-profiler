---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 05:50:56 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 12 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1788169564 89
1788169569 89
1788169574 94
1788169579 94
1788169584 96
1788169589 96
1788169594 96
1788169599 96
1788169604 96
1788169609 96
1788169614 96
1788169619 96
1788169624 96
1788169629 96
1788169634 96
1788169639 96
1788169644 96
1788169649 96
1788169654 96
1788169659 96
```
</details>

---

