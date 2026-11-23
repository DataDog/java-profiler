---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 15:37:59 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 48-68 cores)</summary>

```
1795465933 63
1795465938 68
1795465943 68
1795465948 68
1795465953 68
1795465958 48
1795465963 48
1795465968 48
1795465973 48
1795465978 48
1795465983 48
1795465988 48
1795465993 48
1795465998 48
1795466003 48
1795466008 48
1795466013 48
1795466018 48
1795466023 48
1795466028 48
```
</details>

---

