---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 17:14:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795558278 28
1795558283 28
1795558288 28
1795558293 28
1795558298 28
1795558303 28
1795558308 33
1795558313 33
1795558318 28
1795558323 28
1795558328 28
1795558333 28
1795558338 28
1795558343 28
1795558348 28
1795558353 28
1795558358 28
1795558363 28
1795558368 28
1795558373 28
```
</details>

---

