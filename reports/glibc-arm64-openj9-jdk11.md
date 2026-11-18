---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:20:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 36-51 cores)</summary>

```
1795014945 51
1795014950 51
1795014955 51
1795014960 51
1795014965 51
1795014970 51
1795014975 51
1795014980 41
1795014985 41
1795014990 41
1795014995 41
1795015000 41
1795015006 41
1795015011 36
1795015016 36
1795015021 36
1795015026 41
1795015031 41
1795015036 41
1795015041 41
```
</details>

---

