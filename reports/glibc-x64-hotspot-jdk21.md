---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:45:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 64-70 cores)</summary>

```
1795642907 64
1795642912 64
1795642917 64
1795642922 64
1795642927 64
1795642932 64
1795642937 64
1795642942 64
1795642947 66
1795642952 66
1795642957 66
1795642962 66
1795642967 70
1795642972 70
1795642977 70
1795642982 70
1795642987 70
1795642992 70
1795642997 70
1795643002 70
```
</details>

---

