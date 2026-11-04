---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793801558 30
1793801563 30
1793801568 30
1793801573 30
1793801578 30
1793801583 30
1793801588 30
1793801593 30
1793801598 30
1793801603 30
1793801608 32
1793801613 32
1793801618 32
1793801623 32
1793801628 32
1793801633 32
1793801638 32
1793801643 32
1793801648 32
1793801653 32
```
</details>

---

