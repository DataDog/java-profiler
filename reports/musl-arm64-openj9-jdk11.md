---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:32:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 916 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795094839 50
1795094844 50
1795094849 50
1795094854 50
1795094859 50
1795094864 50
1795094869 50
1795094874 50
1795094879 50
1795094884 50
1795094889 50
1795094894 50
1795094899 50
1795094904 50
1795094909 50
1795094914 50
1795094919 50
1795094924 50
1795094929 50
1795094934 50
```
</details>

---

