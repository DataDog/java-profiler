---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:49:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 87-94 cores)</summary>

```
1795707864 92
1795707869 92
1795707874 92
1795707879 92
1795707884 92
1795707889 92
1795707894 92
1795707899 94
1795707904 94
1795707909 94
1795707914 94
1795707919 94
1795707924 94
1795707929 94
1795707934 94
1795707939 94
1795707944 94
1795707949 94
1795707954 94
1795707959 94
```
</details>

---

