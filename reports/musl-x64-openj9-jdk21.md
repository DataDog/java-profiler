---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 18:02:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789682084 32
1789682089 32
1789682094 32
1789682099 32
1789682104 32
1789682109 30
1789682114 30
1789682119 30
1789682124 30
1789682129 30
1789682134 30
1789682139 30
1789682144 30
1789682149 30
1789682154 30
1789682159 30
1789682164 30
1789682169 30
1789682174 30
1789682179 30
```
</details>

---

