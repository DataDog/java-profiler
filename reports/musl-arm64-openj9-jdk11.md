---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:19:17 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 19-26 cores)</summary>

```
1794582864 19
1794582869 19
1794582874 19
1794582879 19
1794582884 19
1794582889 19
1794582894 19
1794582899 19
1794582904 19
1794582909 19
1794582914 19
1794582919 19
1794582924 24
1794582929 24
1794582934 26
1794582939 26
1794582944 26
1794582949 26
1794582954 26
1794582959 22
```
</details>

---

