---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 42-51 cores)</summary>

```
1795605017 48
1795605022 48
1795605027 48
1795605032 48
1795605037 48
1795605042 48
1795605047 48
1795605052 48
1795605057 48
1795605062 48
1795605067 48
1795605072 48
1795605077 48
1795605082 51
1795605087 51
1795605092 51
1795605097 51
1795605102 51
1795605107 51
1795605112 51
```
</details>

---

