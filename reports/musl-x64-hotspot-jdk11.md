---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1789716414 81
1789716420 81
1789716425 81
1789716430 81
1789716435 81
1789716440 81
1789716445 81
1789716450 81
1789716455 79
1789716460 79
1789716465 79
1789716470 79
1789716475 79
1789716480 79
1789716485 79
1789716490 79
1789716495 79
1789716500 79
1789716505 79
1789716510 77
```
</details>

---

