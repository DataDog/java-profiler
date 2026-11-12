---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:01:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1794477261 32
1794477266 32
1794477271 32
1794477276 32
1794477281 32
1794477286 32
1794477291 32
1794477296 32
1794477301 32
1794477306 32
1794477311 32
1794477316 30
1794477321 30
1794477326 30
1794477331 30
1794477336 30
1794477341 30
1794477346 30
1794477351 30
1794477356 30
```
</details>

---

