---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 12:28:12 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 12 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1793812855 39
1793812860 39
1793812865 39
1793812870 39
1793812875 39
1793812880 39
1793812885 39
1793812890 39
1793812895 39
1793812900 39
1793812905 51
1793812910 51
1793812915 51
1793812920 51
1793812925 51
1793812930 51
1793812935 51
1793812940 51
1793812945 51
1793812950 51
```
</details>

---

