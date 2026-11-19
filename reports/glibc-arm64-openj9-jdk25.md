---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 09:13:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 15 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795097357 50
1795097362 50
1795097367 64
1795097372 64
1795097377 64
1795097382 64
1795097387 64
1795097392 64
1795097397 50
1795097402 50
1795097407 50
1795097412 50
1795097417 50
1795097422 50
1795097427 50
1795097432 50
1795097437 50
1795097442 50
1795097447 50
1795097452 50
```
</details>

---

