---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 01:03:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 12 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1792040338 54
1792040343 54
1792040348 54
1792040353 54
1792040358 54
1792040363 64
1792040368 64
1792040373 64
1792040378 64
1792040383 64
1792040388 64
1792040393 64
1792040398 64
1792040403 64
1792040408 64
1792040413 64
1792040418 64
1792040424 64
1792040429 64
1792040434 64
```
</details>

---

