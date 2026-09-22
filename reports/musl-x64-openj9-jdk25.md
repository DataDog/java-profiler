---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 09:50:46 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 30-38 cores)</summary>

```
1790084734 38
1790084739 30
1790084744 30
1790084749 30
1790084754 30
1790084759 30
1790084764 30
1790084769 30
1790084774 30
1790084779 30
1790084784 30
1790084789 30
1790084794 30
1790084799 30
1790084804 30
1790084809 30
1790084814 30
1790084819 30
1790084824 30
1790084829 30
```
</details>

---

