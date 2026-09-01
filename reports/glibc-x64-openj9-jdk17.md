---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 14:09:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 312 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 64-76 cores)</summary>

```
1788285815 68
1788285820 68
1788285825 68
1788285830 68
1788285835 68
1788285840 68
1788285845 68
1788285850 76
1788285855 76
1788285860 76
1788285865 76
1788285870 76
1788285875 76
1788285880 76
1788285885 76
1788285890 76
1788285895 76
1788285900 76
1788285905 76
1788285910 76
```
</details>

---

