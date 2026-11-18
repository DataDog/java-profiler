---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:33:07 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1795011939 64
1795011944 64
1795011949 64
1795011954 64
1795011959 64
1795011964 64
1795011969 64
1795011974 64
1795011979 64
1795011984 64
1795011989 64
1795011994 64
1795011999 64
1795012004 64
1795012009 64
1795012014 64
1795012019 64
1795012024 64
1795012029 64
1795012034 64
```
</details>

---

