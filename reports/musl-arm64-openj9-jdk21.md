---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 12:33:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 11 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 15 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795022912 51
1795022917 51
1795022922 51
1795022927 51
1795022933 51
1795022938 51
1795022943 51
1795022948 51
1795022953 51
1795022958 51
1795022963 51
1795022968 51
1795022973 51
1795022978 51
1795022983 51
1795022988 51
1795022993 51
1795022998 51
1795023003 46
1795023008 46
```
</details>

---

