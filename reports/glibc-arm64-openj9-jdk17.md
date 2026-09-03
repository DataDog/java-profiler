---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 05:48:52 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 15 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1788428690 20
1788428695 20
1788428700 20
1788428705 20
1788428710 20
1788428715 20
1788428720 20
1788428725 20
1788428730 20
1788428735 20
1788428740 20
1788428745 20
1788428750 20
1788428755 20
1788428760 18
1788428765 18
1788428770 18
1788428775 18
1788428780 18
1788428785 18
```
</details>

---

