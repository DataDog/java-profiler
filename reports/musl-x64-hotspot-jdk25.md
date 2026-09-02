---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 09:19:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1788354655 76
1788354660 76
1788354665 76
1788354670 76
1788354675 76
1788354680 76
1788354685 76
1788354690 76
1788354695 76
1788354700 76
1788354705 76
1788354710 68
1788354715 68
1788354720 68
1788354725 68
1788354730 68
1788354735 68
1788354740 68
1788354745 68
1788354750 68
```
</details>

---

