---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:38:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 33-68 cores)</summary>

```
1789716445 53
1789716450 53
1789716455 53
1789716460 53
1789716465 53
1789716470 53
1789716475 53
1789716480 53
1789716485 53
1789716490 53
1789716495 53
1789716500 53
1789716505 53
1789716510 53
1789716515 53
1789716520 53
1789716525 33
1789716530 33
1789716535 33
1789716540 68
```
</details>

---

