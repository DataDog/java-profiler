---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:04:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792764027 48
1792764032 48
1792764037 48
1792764042 48
1792764047 48
1792764052 48
1792764057 48
1792764062 48
1792764067 48
1792764072 48
1792764077 48
1792764082 48
1792764087 48
1792764092 48
1792764097 48
1792764102 48
1792764107 48
1792764112 48
1792764117 43
1792764122 43
```
</details>

---

