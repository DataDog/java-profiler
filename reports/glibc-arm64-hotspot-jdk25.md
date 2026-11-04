---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 13-30 cores)</summary>

```
1793801611 13
1793801616 13
1793801621 13
1793801626 13
1793801631 13
1793801636 13
1793801641 13
1793801646 30
1793801651 30
1793801656 30
1793801661 30
1793801666 30
1793801671 30
1793801676 30
1793801681 30
1793801686 30
1793801691 30
1793801696 30
1793801701 30
1793801706 30
```
</details>

---

