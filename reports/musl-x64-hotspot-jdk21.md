---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:55:19 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 28-57 cores)</summary>

```
1795380692 28
1795380697 28
1795380702 28
1795380707 28
1795380712 28
1795380717 28
1795380722 28
1795380727 48
1795380732 48
1795380737 48
1795380742 48
1795380747 57
1795380752 57
1795380757 57
1795380762 57
1795380767 57
1795380772 57
1795380777 57
1795380782 57
1795380787 57
```
</details>

---

