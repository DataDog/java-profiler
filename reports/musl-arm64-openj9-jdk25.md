---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:59:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 14 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1794912844 38
1794912849 38
1794912854 38
1794912859 38
1794912864 38
1794912869 38
1794912874 38
1794912879 38
1794912884 38
1794912889 33
1794912894 33
1794912899 33
1794912904 33
1794912909 33
1794912914 33
1794912919 33
1794912924 33
1794912929 33
1794912934 33
1794912939 33
```
</details>

---

