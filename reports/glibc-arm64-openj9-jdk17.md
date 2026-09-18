---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:27:48 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1789737690 44
1789737695 44
1789737700 44
1789737705 44
1789737710 44
1789737715 44
1789737720 44
1789737725 44
1789737730 44
1789737735 44
1789737741 44
1789737746 44
1789737751 44
1789737756 44
1789737761 44
1789737766 44
1789737771 44
1789737776 44
1789737781 48
1789737786 48
```
</details>

---

