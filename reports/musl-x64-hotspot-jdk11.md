---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:29:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1016 |
| Sample Rate | 16.93/sec |
| Health Score | 1058% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794792263 32
1794792268 32
1794792273 32
1794792278 32
1794792283 32
1794792288 32
1794792293 32
1794792298 32
1794792303 32
1794792308 32
1794792313 32
1794792318 32
1794792323 32
1794792328 32
1794792333 32
1794792338 32
1794792343 32
1794792348 32
1794792353 32
1794792358 32
```
</details>

---

