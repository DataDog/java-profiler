---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:22:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793722629 66
1793722634 66
1793722639 66
1793722644 66
1793722649 66
1793722654 66
1793722659 66
1793722664 66
1793722669 64
1793722674 64
1793722679 64
1793722684 64
1793722689 64
1793722694 66
1793722699 66
1793722704 66
1793722709 66
1793722714 66
1793722719 66
1793722724 66
```
</details>

---

