---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 08:13:33 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1793275673 83
1793275678 83
1793275683 83
1793275688 85
1793275693 85
1793275698 85
1793275703 87
1793275708 87
1793275713 87
1793275718 87
1793275723 87
1793275728 87
1793275733 87
1793275738 87
1793275743 87
1793275748 87
1793275753 87
1793275758 87
1793275763 87
1793275768 87
```
</details>

---

