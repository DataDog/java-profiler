---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:53:46 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1036 |
| Sample Rate | 17.27/sec |
| Health Score | 1079% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 83-87 cores)</summary>

```
1792144224 87
1792144229 87
1792144234 87
1792144239 85
1792144244 85
1792144249 85
1792144254 85
1792144259 85
1792144264 85
1792144269 85
1792144274 85
1792144279 85
1792144284 85
1792144289 83
1792144294 83
1792144299 83
1792144304 83
1792144309 83
1792144314 83
1792144319 83
```
</details>

---

