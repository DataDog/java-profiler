---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 08:19:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 591 |

<details>
<summary>CPU Timeline (3 unique values: 13-17 cores)</summary>

```
1795698876 17
1795698881 17
1795698886 17
1795698891 17
1795698896 17
1795698901 17
1795698906 17
1795698911 17
1795698916 17
1795698921 17
1795698926 15
1795698931 15
1795698936 15
1795698941 15
1795698946 15
1795698951 13
1795698956 13
1795698961 15
1795698966 15
1795698971 15
```
</details>

---

