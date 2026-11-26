---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 08:21:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1795698957 47
1795698962 47
1795698967 47
1795698972 47
1795698977 47
1795698982 47
1795698987 47
1795698992 47
1795698997 47
1795699002 47
1795699007 47
1795699012 47
1795699017 51
1795699022 51
1795699027 51
1795699032 51
1795699037 51
1795699042 51
1795699047 51
1795699052 51
```
</details>

---

