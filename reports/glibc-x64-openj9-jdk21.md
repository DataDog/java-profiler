---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 13:04:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1787158820 96
1787158825 96
1787158830 96
1787158835 96
1787158840 96
1787158845 96
1787158850 96
1787158855 96
1787158860 96
1787158865 96
1787158870 96
1787158875 96
1787158880 96
1787158885 96
1787158890 76
1787158895 76
1787158900 76
1787158905 76
1787158910 76
1787158915 76
```
</details>

---

