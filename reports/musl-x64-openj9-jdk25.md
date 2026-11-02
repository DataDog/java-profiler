---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:41:19 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 50-73 cores)</summary>

```
1793633749 73
1793633754 73
1793633759 73
1793633764 73
1793633769 73
1793633774 73
1793633779 73
1793633784 71
1793633789 71
1793633794 71
1793633799 71
1793633804 71
1793633809 71
1793633814 71
1793633819 71
1793633824 71
1793633829 71
1793633834 50
1793633839 50
1793633844 50
```
</details>

---

