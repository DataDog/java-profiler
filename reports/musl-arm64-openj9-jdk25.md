---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:30:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 11 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (5 unique values: 16-29 cores)</summary>

```
1795011899 16
1795011904 16
1795011909 16
1795011914 16
1795011919 16
1795011924 16
1795011929 19
1795011934 19
1795011939 19
1795011944 19
1795011949 19
1795011954 19
1795011959 19
1795011964 19
1795011969 24
1795011974 24
1795011979 24
1795011984 24
1795011989 28
1795011994 28
```
</details>

---

