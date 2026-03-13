---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-13 07:10:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1131 |
| Sample Rate | 18.85/sec |
| Health Score | 1178% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1773399911 81
1773399916 81
1773399921 81
1773399926 81
1773399931 81
1773399936 81
1773399941 79
1773399946 79
1773399951 79
1773399956 79
1773399961 79
1773399966 79
1773399971 79
1773399976 79
1773399981 79
1773399986 79
1773399991 79
1773399996 79
1773400001 75
1773400006 75
```
</details>

---

