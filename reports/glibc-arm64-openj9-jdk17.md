---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:01:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794481032 48
1794481037 48
1794481042 48
1794481047 48
1794481052 48
1794481057 48
1794481062 48
1794481067 48
1794481072 48
1794481077 43
1794481082 43
1794481087 43
1794481092 43
1794481097 43
1794481102 43
1794481107 43
1794481112 43
1794481117 43
1794481122 43
1794481127 43
```
</details>

---

