---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:38:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1789716445 76
1789716450 76
1789716455 76
1789716460 76
1789716465 76
1789716470 76
1789716475 76
1789716480 76
1789716485 76
1789716490 76
1789716495 76
1789716500 76
1789716505 76
1789716510 76
1789716515 96
1789716520 96
1789716525 88
1789716530 88
1789716535 88
1789716540 88
```
</details>

---

