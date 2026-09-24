---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 08:42:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 12 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 7-27 cores)</summary>

```
1790253450 7
1790253455 7
1790253460 7
1790253465 7
1790253470 7
1790253475 7
1790253480 7
1790253485 7
1790253490 7
1790253495 7
1790253500 7
1790253505 7
1790253510 7
1790253515 7
1790253520 7
1790253525 27
1790253530 27
1790253535 27
1790253540 27
1790253545 27
```
</details>

---

