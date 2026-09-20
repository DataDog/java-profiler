---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-20 05:46:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1789897336 13
1789897341 13
1789897346 13
1789897351 18
1789897356 18
1789897361 18
1789897366 18
1789897371 18
1789897376 18
1789897382 18
1789897387 18
1789897392 18
1789897397 18
1789897402 18
1789897407 18
1789897412 18
1789897417 18
1789897422 18
1789897427 18
1789897432 18
```
</details>

---

