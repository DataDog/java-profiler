---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-04 04:47:51 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 48-56 cores)</summary>

```
1777884032 48
1777884037 56
1777884042 56
1777884047 56
1777884052 56
1777884057 56
1777884062 56
1777884067 56
1777884072 56
1777884077 56
1777884082 56
1777884087 56
1777884092 56
1777884097 56
1777884102 56
1777884107 56
1777884112 56
1777884117 56
1777884122 56
1777884127 52
```
</details>

---

