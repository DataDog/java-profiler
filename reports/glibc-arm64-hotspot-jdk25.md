---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:58:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (5 unique values: 32-42 cores)</summary>

```
1794480754 32
1794480759 32
1794480764 32
1794480769 32
1794480774 32
1794480779 32
1794480784 42
1794480789 42
1794480794 39
1794480799 39
1794480804 37
1794480809 37
1794480814 37
1794480819 37
1794480824 37
1794480829 37
1794480834 39
1794480839 39
1794480844 39
1794480849 39
```
</details>

---

