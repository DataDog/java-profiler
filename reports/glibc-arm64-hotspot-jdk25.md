---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:52:56 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 16-47 cores)</summary>

```
1795614525 47
1795614530 47
1795614535 47
1795614540 47
1795614545 47
1795614550 47
1795614555 47
1795614560 47
1795614565 16
1795614570 16
1795614575 16
1795614580 16
1795614585 16
1795614590 16
1795614595 16
1795614600 16
1795614605 16
1795614610 16
1795614615 16
1795614620 16
```
</details>

---

