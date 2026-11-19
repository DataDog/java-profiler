---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:23:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 10 |
| Allocations | 158 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795108695 50
1795108700 50
1795108705 50
1795108710 50
1795108715 50
1795108720 50
1795108725 50
1795108730 50
1795108735 50
1795108740 50
1795108745 50
1795108750 50
1795108755 50
1795108760 50
1795108765 50
1795108770 50
1795108775 50
1795108780 50
1795108785 50
1795108790 36
```
</details>

---

