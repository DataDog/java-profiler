---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:22:10 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 87-96 cores)</summary>

```
1778537943 87
1778537948 87
1778537953 92
1778537958 92
1778537963 92
1778537968 92
1778537973 92
1778537978 92
1778537983 92
1778537988 92
1778537993 92
1778537998 92
1778538003 92
1778538008 92
1778538013 92
1778538018 96
1778538023 96
1778538028 96
1778538033 96
1778538038 96
```
</details>

---

