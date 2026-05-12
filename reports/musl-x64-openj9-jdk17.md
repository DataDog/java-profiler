---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 02:17:05 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1778566269 44
1778566274 44
1778566279 48
1778566284 48
1778566289 48
1778566294 48
1778566299 48
1778566304 48
1778566309 48
1778566314 48
1778566319 48
1778566324 48
1778566329 48
1778566334 48
1778566339 48
1778566344 48
1778566349 48
1778566354 48
1778566359 48
1778566364 48
```
</details>

---

