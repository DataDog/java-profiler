---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794484224 29
1794484229 29
1794484234 29
1794484239 29
1794484244 27
1794484249 27
1794484254 27
1794484259 27
1794484264 29
1794484269 29
1794484274 29
1794484279 29
1794484284 29
1794484289 29
1794484294 29
1794484299 29
1794484304 29
1794484309 29
1794484314 29
1794484319 29
```
</details>

---

