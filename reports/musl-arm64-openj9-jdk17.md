---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 10 |
| Allocations | 130 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 15 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795014951 38
1795014956 38
1795014961 38
1795014966 38
1795014971 38
1795014976 38
1795014981 38
1795014986 38
1795014991 43
1795014996 43
1795015001 43
1795015006 43
1795015011 43
1795015016 43
1795015021 43
1795015026 43
1795015031 43
1795015036 43
1795015041 43
1795015046 43
```
</details>

---

