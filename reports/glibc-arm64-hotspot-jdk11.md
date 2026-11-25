---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:29:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 6 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795627446 42
1795627451 42
1795627456 42
1795627461 42
1795627466 42
1795627471 42
1795627476 42
1795627481 42
1795627486 42
1795627491 42
1795627496 42
1795627501 42
1795627506 47
1795627511 47
1795627516 47
1795627521 47
1795627526 47
1795627531 47
1795627536 47
1795627541 47
```
</details>

---

