---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 23-29 cores)</summary>

```
1792686190 29
1792686195 29
1792686200 29
1792686205 27
1792686210 27
1792686215 27
1792686220 27
1792686225 27
1792686230 27
1792686235 29
1792686240 29
1792686245 29
1792686250 29
1792686255 29
1792686260 23
1792686265 23
1792686270 23
1792686275 23
1792686280 23
1792686285 23
```
</details>

---

