---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 10:08:26 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 61-65 cores)</summary>

```
1790690579 65
1790690584 65
1790690589 65
1790690594 65
1790690599 65
1790690604 65
1790690609 63
1790690614 63
1790690619 63
1790690624 63
1790690629 63
1790690634 63
1790690639 63
1790690644 63
1790690649 63
1790690654 63
1790690659 63
1790690664 63
1790690669 63
1790690674 63
```
</details>

---

