---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793801702 32
1793801707 32
1793801712 32
1793801717 32
1793801722 32
1793801727 32
1793801732 32
1793801737 32
1793801742 32
1793801747 32
1793801752 32
1793801757 32
1793801762 32
1793801767 32
1793801772 32
1793801777 32
1793801782 32
1793801787 32
1793801792 32
1793801797 30
```
</details>

---

