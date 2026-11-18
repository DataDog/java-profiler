---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:34:15 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795005022 51
1795005027 51
1795005032 51
1795005037 51
1795005042 51
1795005047 51
1795005052 51
1795005057 51
1795005062 51
1795005067 51
1795005072 51
1795005077 51
1795005082 51
1795005087 51
1795005092 51
1795005097 51
1795005102 51
1795005107 51
1795005112 51
1795005117 51
```
</details>

---

