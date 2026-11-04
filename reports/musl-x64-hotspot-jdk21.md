---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 50-54 cores)</summary>

```
1793801548 50
1793801553 50
1793801558 50
1793801563 50
1793801568 50
1793801573 50
1793801578 50
1793801583 50
1793801588 50
1793801593 50
1793801598 52
1793801603 52
1793801608 52
1793801613 52
1793801618 54
1793801623 54
1793801628 54
1793801633 54
1793801638 54
1793801643 54
```
</details>

---

