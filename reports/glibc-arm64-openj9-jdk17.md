---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:22:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 14 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793722634 51
1793722639 51
1793722644 51
1793722649 51
1793722654 51
1793722659 51
1793722664 51
1793722669 51
1793722674 51
1793722679 51
1793722684 51
1793722689 51
1793722694 51
1793722699 51
1793722704 51
1793722709 51
1793722714 51
1793722719 51
1793722724 51
1793722729 51
```
</details>

---

