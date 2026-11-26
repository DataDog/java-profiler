---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 05:52:46 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 62-68 cores)</summary>

```
1795690065 62
1795690070 62
1795690075 62
1795690080 62
1795690085 62
1795690090 62
1795690095 62
1795690100 62
1795690105 62
1795690110 62
1795690115 62
1795690120 62
1795690125 62
1795690130 62
1795690135 62
1795690140 62
1795690145 65
1795690150 65
1795690155 65
1795690160 65
```
</details>

---

