---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:08:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 20-21 cores)</summary>

```
1789995735 20
1789995740 21
1789995745 21
1789995750 21
1789995755 21
1789995760 21
1789995765 21
1789995770 21
1789995775 21
1789995780 21
1789995785 21
1789995790 21
1789995795 21
1789995800 21
1789995805 21
1789995810 21
1789995815 21
1789995820 21
1789995825 21
1789995830 21
```
</details>

---

