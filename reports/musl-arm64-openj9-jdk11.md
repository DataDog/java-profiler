---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:59:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1094 |
| Sample Rate | 18.23/sec |
| Health Score | 1139% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1790780038 31
1790780043 31
1790780048 31
1790780053 31
1790780058 31
1790780063 31
1790780068 31
1790780073 31
1790780078 31
1790780083 31
1790780088 31
1790780093 31
1790780098 31
1790780103 31
1790780108 31
1790780113 31
1790780118 31
1790780123 31
1790780128 31
1790780133 31
```
</details>

---

