---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793801551 66
1793801556 66
1793801561 66
1793801566 66
1793801571 66
1793801576 66
1793801581 66
1793801586 66
1793801591 66
1793801596 66
1793801601 66
1793801606 66
1793801611 66
1793801616 66
1793801621 66
1793801626 66
1793801631 66
1793801636 66
1793801641 64
1793801646 64
```
</details>

---

