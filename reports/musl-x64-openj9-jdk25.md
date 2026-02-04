---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 13:53:17 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 431 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1770230749 64
1770230754 64
1770230759 64
1770230764 64
1770230769 64
1770230774 62
1770230779 62
1770230784 62
1770230789 62
1770230795 64
1770230800 64
1770230805 64
1770230810 64
1770230815 64
1770230820 64
1770230825 64
1770230830 64
1770230835 64
1770230840 64
1770230845 64
```
</details>

---

