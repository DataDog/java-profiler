---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 20:28:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 75-96 cores)</summary>

```
1794792252 75
1794792257 75
1794792262 75
1794792267 75
1794792272 75
1794792277 96
1794792282 96
1794792287 96
1794792292 94
1794792297 94
1794792302 94
1794792308 94
1794792313 94
1794792318 94
1794792323 94
1794792328 94
1794792333 96
1794792338 96
1794792343 96
1794792348 96
```
</details>

---

