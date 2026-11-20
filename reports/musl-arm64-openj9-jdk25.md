---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 13:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 10 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795197719 50
1795197724 50
1795197729 50
1795197734 50
1795197739 50
1795197744 50
1795197749 50
1795197754 50
1795197759 50
1795197764 50
1795197769 50
1795197774 50
1795197779 50
1795197784 50
1795197789 50
1795197794 50
1795197799 50
1795197804 50
1795197809 50
1795197814 50
```
</details>

---

