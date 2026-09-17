---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:55:08 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789678047 96
1789678053 96
1789678058 96
1789678063 94
1789678068 94
1789678073 94
1789678078 94
1789678083 94
1789678088 94
1789678093 94
1789678098 94
1789678103 94
1789678108 94
1789678113 94
1789678118 94
1789678123 94
1789678128 94
1789678133 94
1789678138 94
1789678143 94
```
</details>

---

