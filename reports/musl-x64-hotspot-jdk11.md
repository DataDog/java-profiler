---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 25-28 cores)</summary>

```
1793801556 25
1793801561 25
1793801566 25
1793801571 25
1793801576 25
1793801581 25
1793801586 25
1793801591 25
1793801596 25
1793801601 25
1793801606 25
1793801611 25
1793801616 25
1793801621 25
1793801626 25
1793801631 25
1793801636 25
1793801641 28
1793801646 28
1793801651 28
```
</details>

---

