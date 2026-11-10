---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 09:12:49 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 9 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (3 unique values: 37-45 cores)</summary>

```
1794319690 37
1794319695 37
1794319700 37
1794319705 37
1794319710 37
1794319715 37
1794319720 37
1794319725 37
1794319730 39
1794319735 39
1794319740 37
1794319745 37
1794319750 37
1794319755 37
1794319760 37
1794319765 37
1794319770 37
1794319775 37
1794319780 39
1794319785 39
```
</details>

---

