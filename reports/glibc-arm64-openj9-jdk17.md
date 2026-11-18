---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:22:10 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 11 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 12 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1795025935 49
1795025940 49
1795025945 51
1795025950 51
1795025955 51
1795025960 51
1795025965 51
1795025970 51
1795025975 51
1795025980 51
1795025985 51
1795025990 51
1795025995 51
1795026000 51
1795026005 51
1795026010 51
1795026015 51
1795026020 51
1795026025 51
1795026030 51
```
</details>

---

