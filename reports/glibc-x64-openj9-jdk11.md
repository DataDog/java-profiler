---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 16:32:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 45-66 cores)</summary>

```
1795382890 47
1795382895 47
1795382900 47
1795382905 47
1795382910 47
1795382915 47
1795382920 47
1795382925 47
1795382930 45
1795382935 45
1795382940 45
1795382945 45
1795382950 45
1795382955 66
1795382960 66
1795382965 49
1795382970 49
1795382975 49
1795382980 49
1795382985 49
```
</details>

---

