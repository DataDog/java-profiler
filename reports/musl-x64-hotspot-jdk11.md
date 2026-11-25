---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 65-74 cores)</summary>

```
1795618876 67
1795618881 74
1795618886 74
1795618891 65
1795618896 65
1795618901 65
1795618906 65
1795618911 70
1795618916 70
1795618921 70
1795618926 70
1795618931 70
1795618936 70
1795618941 70
1795618946 70
1795618951 70
1795618956 70
1795618961 70
1795618966 70
1795618971 70
```
</details>

---

