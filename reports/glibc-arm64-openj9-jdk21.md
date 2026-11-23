---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 12:00:51 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795452941 54
1795452946 54
1795452951 54
1795452956 54
1795452961 54
1795452966 54
1795452971 54
1795452976 54
1795452981 54
1795452986 54
1795452991 54
1795452996 59
1795453001 59
1795453006 59
1795453011 59
1795453016 59
1795453021 59
1795453026 59
1795453031 59
1795453036 59
```
</details>

---

