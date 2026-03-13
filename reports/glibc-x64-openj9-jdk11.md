---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-13 07:10:01 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 51-77 cores)</summary>

```
1773399941 51
1773399946 76
1773399951 76
1773399956 76
1773399961 76
1773399966 76
1773399971 76
1773399976 76
1773399981 77
1773399986 77
1773399991 77
1773399996 77
1773400001 77
1773400006 77
1773400011 77
1773400016 77
1773400021 77
1773400026 77
1773400031 77
1773400036 77
```
</details>

---

