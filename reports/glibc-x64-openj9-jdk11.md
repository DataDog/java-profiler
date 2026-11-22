---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 15:36:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 8 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 16-51 cores)</summary>

```
1795379506 16
1795379511 16
1795379516 16
1795379521 16
1795379526 16
1795379531 16
1795379536 16
1795379541 49
1795379546 49
1795379551 49
1795379556 49
1795379561 49
1795379566 49
1795379571 51
1795379576 51
1795379581 51
1795379586 51
1795379591 51
1795379596 51
1795379601 51
```
</details>

---

