---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:29:29 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795630982 47
1795630987 47
1795630992 47
1795630997 47
1795631002 47
1795631007 47
1795631012 47
1795631017 47
1795631022 47
1795631027 47
1795631032 47
1795631037 47
1795631042 47
1795631047 47
1795631052 47
1795631057 64
1795631062 64
1795631067 47
1795631072 47
1795631077 47
```
</details>

---

