---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 51-57 cores)</summary>

```
1789992204 51
1789992209 51
1789992214 51
1789992219 51
1789992224 51
1789992229 53
1789992234 53
1789992239 55
1789992244 55
1789992249 55
1789992254 55
1789992259 55
1789992264 55
1789992269 55
1789992274 55
1789992279 57
1789992284 57
1789992289 57
1789992294 57
1789992299 57
```
</details>

---

