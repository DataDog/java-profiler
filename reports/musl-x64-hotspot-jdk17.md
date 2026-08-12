---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 11:23:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1786547861 93
1786547866 93
1786547871 93
1786547876 86
1786547881 86
1786547886 86
1786547891 86
1786547896 86
1786547901 86
1786547906 86
1786547911 86
1786547916 86
1786547921 86
1786547926 86
1786547931 86
1786547936 86
1786547941 86
1786547946 96
1786547951 96
1786547956 96
```
</details>

---

