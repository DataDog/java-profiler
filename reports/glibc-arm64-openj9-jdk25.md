---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:57:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (7 unique values: 38-57 cores)</summary>

```
1794498739 49
1794498744 49
1794498749 43
1794498754 43
1794498759 40
1794498764 40
1794498769 40
1794498774 40
1794498779 40
1794498784 38
1794498789 38
1794498794 40
1794498799 40
1794498804 40
1794498809 40
1794498814 40
1794498819 40
1794498824 40
1794498829 40
1794498834 42
```
</details>

---

