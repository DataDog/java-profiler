---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 11 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 39-49 cores)</summary>

```
1793801548 42
1793801553 42
1793801558 44
1793801563 44
1793801568 39
1793801573 39
1793801578 39
1793801583 39
1793801588 39
1793801593 39
1793801598 39
1793801603 39
1793801608 39
1793801613 39
1793801618 44
1793801623 44
1793801628 44
1793801633 44
1793801638 49
1793801643 49
```
</details>

---

