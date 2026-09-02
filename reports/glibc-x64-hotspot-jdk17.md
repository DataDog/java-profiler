---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 10 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788370013 96
1788370018 96
1788370023 96
1788370028 96
1788370033 96
1788370038 96
1788370043 96
1788370048 96
1788370053 96
1788370058 96
1788370063 96
1788370068 88
1788370073 88
1788370078 88
1788370083 88
1788370088 88
1788370093 88
1788370098 88
1788370103 88
1788370108 88
```
</details>

---

