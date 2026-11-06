---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 00:04:46 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1793941229 29
1793941234 29
1793941239 29
1793941244 29
1793941249 29
1793941254 29
1793941259 29
1793941264 29
1793941269 29
1793941274 29
1793941279 29
1793941284 29
1793941289 29
1793941294 29
1793941299 29
1793941304 29
1793941309 29
1793941314 29
1793941319 29
1793941324 29
```
</details>

---

