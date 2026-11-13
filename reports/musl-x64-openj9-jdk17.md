---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:24:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794594012 94
1794594017 94
1794594022 94
1794594027 94
1794594032 94
1794594037 94
1794594042 92
1794594047 92
1794594052 92
1794594057 92
1794594062 92
1794594067 92
1794594072 92
1794594077 92
1794594082 92
1794594087 92
1794594092 92
1794594097 92
1794594102 92
1794594107 92
```
</details>

---

