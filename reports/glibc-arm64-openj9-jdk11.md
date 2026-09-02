---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 09:19:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788354660 32
1788354665 32
1788354670 32
1788354675 32
1788354680 32
1788354685 32
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
1788354751 32
1788354756 32
```
</details>

---

