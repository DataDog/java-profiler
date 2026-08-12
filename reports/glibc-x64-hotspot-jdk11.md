---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1786547886 82
1786547891 82
1786547896 82
1786547901 82
1786547906 82
1786547911 87
1786547916 87
1786547921 85
1786547926 85
1786547931 85
1786547936 85
1786547941 85
1786547946 85
1786547951 85
1786547956 85
1786547961 85
1786547966 85
1786547971 85
1786547976 87
1786547981 87
```
</details>

---

