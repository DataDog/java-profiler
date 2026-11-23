---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:59:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795452961 34
1795452966 34
1795452971 34
1795452976 34
1795452981 34
1795452986 34
1795452991 34
1795452996 34
1795453001 34
1795453006 34
1795453011 32
1795453016 32
1795453021 32
1795453026 32
1795453031 32
1795453036 32
1795453041 32
1795453046 32
1795453051 32
1795453056 32
```
</details>

---

