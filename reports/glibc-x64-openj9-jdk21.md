---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (5 unique values: 80-96 cores)</summary>

```
1777557263 80
1777557268 80
1777557273 82
1777557278 82
1777557283 82
1777557288 82
1777557293 82
1777557298 81
1777557303 81
1777557308 81
1777557313 82
1777557318 82
1777557323 82
1777557328 82
1777557333 96
1777557338 96
1777557343 96
1777557348 92
1777557353 92
1777557358 92
```
</details>

---

