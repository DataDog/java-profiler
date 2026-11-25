---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:45:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 7 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795642922 50
1795642927 50
1795642932 50
1795642937 50
1795642942 50
1795642947 50
1795642952 50
1795642957 50
1795642962 50
1795642967 50
1795642972 50
1795642977 50
1795642982 50
1795642987 50
1795642992 50
1795642997 50
1795643002 50
1795643007 50
1795643012 50
1795643017 50
```
</details>

---

