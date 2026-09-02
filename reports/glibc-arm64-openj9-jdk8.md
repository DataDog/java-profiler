---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-02 09:19:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1788354645 45
1788354650 45
1788354655 45
1788354660 45
1788354665 45
1788354670 45
1788354675 40
1788354680 40
1788354685 40
1788354690 40
1788354695 40
1788354700 40
1788354705 40
1788354710 40
1788354715 40
1788354720 40
1788354725 45
1788354730 45
1788354735 44
1788354740 44
```
</details>

---

