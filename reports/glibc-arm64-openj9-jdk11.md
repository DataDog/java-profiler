---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:49:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 13 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795430754 43
1795430759 48
1795430764 48
1795430769 48
1795430774 48
1795430779 48
1795430784 48
1795430789 48
1795430794 48
1795430799 48
1795430804 48
1795430809 48
1795430814 48
1795430819 48
1795430824 48
1795430829 48
1795430834 48
1795430839 48
1795430844 48
1795430849 48
```
</details>

---

