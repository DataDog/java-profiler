---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-27 21:22:39 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 8 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 9-17 cores)</summary>

```
1790558258 9
1790558263 9
1790558268 9
1790558273 9
1790558278 17
1790558283 17
1790558288 17
1790558293 17
1790558298 17
1790558303 17
1790558308 17
1790558313 17
1790558318 17
1790558323 17
1790558328 17
1790558333 17
1790558338 17
1790558343 17
1790558348 17
1790558353 17
```
</details>

---

