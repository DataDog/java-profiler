---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:10:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1789686359 29
1789686364 29
1789686369 29
1789686374 29
1789686379 9
1789686384 9
1789686389 9
1789686394 9
1789686399 9
1789686404 9
1789686409 9
1789686414 9
1789686419 9
1789686424 9
1789686429 9
1789686434 9
1789686439 9
1789686444 9
1789686449 9
1789686454 9
```
</details>

---

