---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 16:40:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1792787814 29
1792787819 29
1792787824 29
1792787829 29
1792787834 29
1792787839 29
1792787844 29
1792787849 29
1792787854 29
1792787859 29
1792787864 29
1792787869 29
1792787874 29
1792787880 29
1792787885 29
1792787890 29
1792787895 29
1792787900 29
1792787905 29
1792787910 32
```
</details>

---

