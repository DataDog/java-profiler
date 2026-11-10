---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:21:06 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1794323779 48
1794323784 48
1794323789 48
1794323794 48
1794323799 48
1794323804 47
1794323809 47
1794323814 47
1794323819 47
1794323824 48
1794323829 48
1794323834 48
1794323839 48
1794323844 48
1794323849 48
1794323854 46
1794323859 46
1794323864 46
1794323869 46
1794323874 46
```
</details>

---

