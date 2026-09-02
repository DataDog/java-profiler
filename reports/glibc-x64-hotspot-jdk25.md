---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 09:19:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1788354655 24
1788354660 24
1788354665 24
1788354670 24
1788354675 24
1788354680 24
1788354685 24
1788354690 32
1788354695 32
1788354700 32
1788354705 32
1788354710 32
1788354715 32
1788354720 32
1788354725 32
1788354730 32
1788354735 32
1788354740 32
1788354745 32
1788354750 32
```
</details>

---

