---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:36:13 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 33-66 cores)</summary>

```
1795379506 33
1795379511 33
1795379516 33
1795379521 66
1795379526 66
1795379531 66
1795379536 66
1795379541 66
1795379546 66
1795379551 66
1795379556 66
1795379561 66
1795379566 66
1795379571 66
1795379576 66
1795379581 66
1795379586 66
1795379591 66
1795379596 66
1795379601 66
```
</details>

---

