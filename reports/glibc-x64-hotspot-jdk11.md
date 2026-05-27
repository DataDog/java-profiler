---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-27 06:39:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 961 |
| Sample Rate | 16.02/sec |
| Health Score | 1001% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 67-71 cores)</summary>

```
1779878207 67
1779878212 67
1779878217 67
1779878222 67
1779878227 67
1779878232 67
1779878237 71
1779878242 71
1779878247 71
1779878252 71
1779878257 71
1779878262 71
1779878267 71
1779878272 71
1779878277 71
1779878282 71
1779878287 71
1779878292 71
1779878297 71
1779878302 71
```
</details>

---

