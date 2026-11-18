---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 40-61 cores)</summary>

```
1794999734 52
1794999739 52
1794999744 61
1794999749 61
1794999754 61
1794999759 61
1794999764 61
1794999769 40
1794999774 40
1794999779 40
1794999784 40
1794999789 40
1794999794 40
1794999799 40
1794999804 40
1794999809 40
1794999814 40
1794999819 40
1794999824 40
1794999829 40
```
</details>

---

