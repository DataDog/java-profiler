---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 13:00:30 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 11 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 13 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 34-48 cores)</summary>

```
1772819703 34
1772819708 34
1772819713 43
1772819718 43
1772819723 43
1772819728 43
1772819733 43
1772819738 43
1772819744 43
1772819749 43
1772819754 43
1772819759 48
1772819764 48
1772819769 48
1772819774 48
1772819779 48
1772819784 48
1772819789 48
1772819794 48
1772819799 48
```
</details>

---

