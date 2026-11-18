---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 14:09:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 17-26 cores)</summary>

```
1795028621 26
1795028626 26
1795028631 26
1795028636 26
1795028641 26
1795028646 26
1795028651 17
1795028656 17
1795028661 17
1795028666 17
1795028671 17
1795028676 17
1795028681 17
1795028686 17
1795028691 17
1795028696 17
1795028701 17
1795028706 17
1795028711 17
1795028716 17
```
</details>

---

