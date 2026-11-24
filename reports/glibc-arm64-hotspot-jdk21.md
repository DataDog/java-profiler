---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 12 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795529401 48
1795529406 48
1795529411 48
1795529416 48
1795529421 48
1795529426 48
1795529431 48
1795529436 48
1795529441 48
1795529446 48
1795529451 48
1795529456 48
1795529461 48
1795529466 48
1795529471 48
1795529476 48
1795529481 48
1795529486 48
1795529491 48
1795529496 48
```
</details>

---

