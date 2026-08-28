---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-28 08:25:46 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 82 |
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
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 82-91 cores)</summary>

```
1787919673 91
1787919678 91
1787919683 91
1787919688 91
1787919693 91
1787919698 91
1787919703 91
1787919708 85
1787919713 85
1787919718 85
1787919723 85
1787919728 85
1787919733 85
1787919738 85
1787919743 85
1787919748 85
1787919753 85
1787919758 85
1787919763 85
1787919768 90
```
</details>

---

