---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-18 21:28:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792373044 48
1792373049 48
1792373054 48
1792373059 48
1792373064 48
1792373069 48
1792373074 48
1792373079 48
1792373084 48
1792373089 48
1792373094 48
1792373099 48
1792373104 48
1792373109 48
1792373114 48
1792373119 48
1792373124 48
1792373129 48
1792373134 43
1792373139 43
```
</details>

---

