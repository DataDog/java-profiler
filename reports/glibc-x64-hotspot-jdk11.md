---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-15 09:57:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 942 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 74-80 cores)</summary>

```
1792072257 80
1792072262 80
1792072267 74
1792072272 74
1792072277 74
1792072282 74
1792072287 74
1792072292 74
1792072297 74
1792072302 74
1792072307 74
1792072312 74
1792072317 76
1792072322 76
1792072327 76
1792072332 76
1792072337 76
1792072342 76
1792072347 76
1792072352 76
```
</details>

---

