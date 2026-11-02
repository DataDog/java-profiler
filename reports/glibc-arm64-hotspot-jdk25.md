---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 06:22:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 10 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1793618332 35
1793618337 35
1793618342 35
1793618347 39
1793618352 39
1793618357 39
1793618362 39
1793618367 39
1793618372 39
1793618377 39
1793618382 39
1793618387 39
1793618392 39
1793618397 39
1793618402 39
1793618407 40
1793618412 40
1793618417 40
1793618422 40
1793618427 40
```
</details>

---

