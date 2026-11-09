---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-09 12:24:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1794244734 30
1794244739 32
1794244744 32
1794244749 32
1794244754 32
1794244759 12
1794244764 12
1794244769 12
1794244774 12
1794244779 12
1794244784 12
1794244789 12
1794244794 12
1794244799 12
1794244804 12
1794244809 12
1794244814 12
1794244819 12
1794244824 12
1794244829 12
```
</details>

---

