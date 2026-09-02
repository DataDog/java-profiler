---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 09:15:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 15 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788354650 62
1788354655 62
1788354660 62
1788354665 62
1788354670 64
1788354675 64
1788354680 64
1788354685 64
1788354690 62
1788354695 62
1788354700 62
1788354705 62
1788354710 62
1788354715 62
1788354720 62
1788354725 62
1788354730 62
1788354735 62
1788354740 62
1788354745 62
```
</details>

---

