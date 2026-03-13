---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-13 07:10:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 78-85 cores)</summary>

```
1773399915 85
1773399920 85
1773399925 85
1773399930 85
1773399935 82
1773399940 82
1773399945 82
1773399950 80
1773399955 80
1773399960 82
1773399965 82
1773399970 82
1773399975 78
1773399980 78
1773399985 83
1773399991 83
1773399996 83
1773400001 81
1773400006 81
1773400011 81
```
</details>

---

