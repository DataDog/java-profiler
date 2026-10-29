---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 11:50:46 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1793288586 68
1793288591 68
1793288596 68
1793288601 68
1793288606 68
1793288611 70
1793288616 70
1793288621 70
1793288626 66
1793288631 66
1793288636 66
1793288641 66
1793288646 66
1793288651 66
1793288656 66
1793288661 66
1793288666 66
1793288671 66
1793288676 66
1793288681 66
```
</details>

---

