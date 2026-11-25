---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:12 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 48-56 cores)</summary>

```
1795618878 56
1795618883 56
1795618888 48
1795618893 48
1795618898 48
1795618903 48
1795618908 48
1795618913 48
1795618918 48
1795618923 48
1795618928 48
1795618933 48
1795618938 48
1795618943 48
1795618948 48
1795618953 48
1795618958 48
1795618963 48
1795618968 48
1795618973 48
```
</details>

---

