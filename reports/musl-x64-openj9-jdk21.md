---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:22:18 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (6 unique values: 54-64 cores)</summary>

```
1793722609 61
1793722614 61
1793722619 61
1793722624 61
1793722629 58
1793722634 58
1793722639 58
1793722644 58
1793722649 58
1793722654 58
1793722659 58
1793722664 58
1793722669 54
1793722674 54
1793722679 54
1793722684 56
1793722689 56
1793722694 56
1793722699 56
1793722704 54
```
</details>

---

