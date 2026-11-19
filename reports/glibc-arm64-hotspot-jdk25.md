---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 05:17:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 13 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (3 unique values: 41-43 cores)</summary>

```
1795083281 42
1795083286 42
1795083291 41
1795083296 41
1795083301 42
1795083306 42
1795083311 42
1795083316 42
1795083321 42
1795083326 42
1795083331 42
1795083336 42
1795083341 43
1795083346 43
1795083351 43
1795083356 43
1795083361 43
1795083366 43
1795083371 42
1795083376 42
```
</details>

---

