---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793801548 30
1793801553 30
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
1793801608 30
1793801613 30
1793801618 30
1793801623 30
1793801628 30
1793801633 30
1793801638 30
1793801643 30
```
</details>

---

