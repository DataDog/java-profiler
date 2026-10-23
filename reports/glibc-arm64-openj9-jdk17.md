---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 10:04:35 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (5 unique values: 37-44 cores)</summary>

```
1792764032 40
1792764037 44
1792764042 44
1792764047 44
1792764052 44
1792764057 41
1792764062 41
1792764067 41
1792764072 41
1792764077 42
1792764082 42
1792764087 42
1792764092 42
1792764097 42
1792764102 42
1792764107 40
1792764112 40
1792764117 37
1792764122 37
1792764127 37
```
</details>

---

