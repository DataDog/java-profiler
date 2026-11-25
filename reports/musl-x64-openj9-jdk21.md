---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:29:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 51-63 cores)</summary>

```
1795620214 61
1795620219 61
1795620224 61
1795620229 61
1795620234 61
1795620239 61
1795620244 61
1795620249 61
1795620254 61
1795620259 61
1795620264 61
1795620269 63
1795620274 63
1795620279 51
1795620284 51
1795620289 51
1795620294 51
1795620299 53
1795620304 53
1795620309 53
```
</details>

---

