---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:11:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1789686363 42
1789686368 42
1789686374 42
1789686379 43
1789686384 43
1789686389 43
1789686394 43
1789686399 43
1789686404 43
1789686409 43
1789686414 43
1789686419 43
1789686424 43
1789686429 43
1789686434 43
1789686439 43
1789686444 43
1789686449 43
1789686454 43
1789686459 43
```
</details>

---

