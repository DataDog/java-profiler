---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 05:46:54 EDT

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
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1786959755 94
1786959760 94
1786959765 94
1786959770 92
1786959775 92
1786959780 92
1786959785 94
1786959790 94
1786959795 96
1786959800 96
1786959805 96
1786959810 96
1786959815 96
1786959820 96
1786959825 96
1786959830 96
1786959835 96
1786959840 96
1786959845 96
1786959850 96
```
</details>

---

