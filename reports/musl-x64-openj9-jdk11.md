---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:04:42 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 74-82 cores)</summary>

```
1777557362 82
1777557367 82
1777557372 82
1777557377 82
1777557382 82
1777557387 82
1777557392 82
1777557397 82
1777557402 78
1777557407 78
1777557412 78
1777557417 78
1777557422 78
1777557427 74
1777557432 74
1777557437 74
1777557442 74
1777557447 74
1777557452 78
1777557457 78
```
</details>

---

