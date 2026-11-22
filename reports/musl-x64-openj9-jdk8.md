---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-22 05:47:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1795344216 51
1795344221 51
1795344226 51
1795344231 51
1795344236 51
1795344241 51
1795344246 51
1795344251 51
1795344256 51
1795344261 49
1795344266 49
1795344271 49
1795344276 49
1795344281 49
1795344286 49
1795344291 49
1795344296 49
1795344301 49
1795344306 49
1795344311 47
```
</details>

---

