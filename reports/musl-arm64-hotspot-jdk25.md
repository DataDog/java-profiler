---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 11 |
| Allocations | 114 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 45-46 cores)</summary>

```
1793801541 46
1793801546 46
1793801551 46
1793801556 46
1793801561 46
1793801566 46
1793801571 46
1793801576 46
1793801581 46
1793801586 46
1793801591 46
1793801596 46
1793801601 46
1793801606 46
1793801611 46
1793801616 46
1793801621 46
1793801626 46
1793801631 45
1793801636 45
```
</details>

---

