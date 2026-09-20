---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-20 05:46:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1789897341 29
1789897346 29
1789897351 29
1789897356 29
1789897361 29
1789897366 29
1789897371 29
1789897376 29
1789897381 29
1789897386 29
1789897391 29
1789897396 29
1789897401 29
1789897406 29
1789897411 29
1789897416 34
1789897421 34
1789897426 34
1789897431 34
1789897436 34
```
</details>

---

