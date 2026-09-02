---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 09:19:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1788354665 46
1788354670 46
1788354675 46
1788354680 47
1788354685 47
1788354690 48
1788354695 48
1788354700 46
1788354705 46
1788354710 46
1788354715 46
1788354720 46
1788354725 46
1788354730 46
1788354735 46
1788354740 46
1788354745 46
1788354750 46
1788354755 46
1788354760 46
```
</details>

---

