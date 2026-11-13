---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 17:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 30-32 cores)</summary>

```
1794608253 31
1794608258 31
1794608263 31
1794608268 31
1794608273 31
1794608278 31
1794608283 32
1794608288 32
1794608293 32
1794608298 32
1794608303 32
1794608308 32
1794608313 32
1794608318 32
1794608323 30
1794608328 30
1794608333 30
1794608338 30
1794608343 30
1794608348 30
```
</details>

---

