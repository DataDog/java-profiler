---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:28:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 23-24 cores)</summary>

```
1795630961 24
1795630966 24
1795630971 24
1795630976 24
1795630981 24
1795630986 24
1795630991 24
1795630996 24
1795631001 24
1795631007 24
1795631012 24
1795631017 24
1795631022 24
1795631027 24
1795631032 24
1795631037 24
1795631042 24
1795631047 24
1795631052 24
1795631057 24
```
</details>

---

