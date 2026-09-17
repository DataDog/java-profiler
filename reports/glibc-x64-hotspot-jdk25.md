---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 19:11:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 82-96 cores)</summary>

```
1789686374 84
1789686379 82
1789686384 82
1789686389 82
1789686394 82
1789686399 82
1789686404 82
1789686409 84
1789686414 84
1789686419 96
1789686424 96
1789686429 96
1789686434 96
1789686439 96
1789686444 96
1789686449 96
1789686454 96
1789686459 96
1789686464 96
1789686469 96
```
</details>

---

