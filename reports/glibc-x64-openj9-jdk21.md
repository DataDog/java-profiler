---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:59:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
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
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1795452946 28
1795452951 28
1795452956 28
1795452961 28
1795452966 28
1795452971 28
1795452976 28
1795452981 30
1795452986 30
1795452991 30
1795452996 30
1795453001 30
1795453006 30
1795453011 30
1795453016 30
1795453021 30
1795453026 30
1795453031 30
1795453036 30
1795453041 30
```
</details>

---

