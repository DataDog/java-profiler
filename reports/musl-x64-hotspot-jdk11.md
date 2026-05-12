---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1778582414 28
1778582419 28
1778582424 28
1778582429 28
1778582434 28
1778582439 28
1778582444 28
1778582450 28
1778582455 26
1778582460 26
1778582465 28
1778582470 28
1778582475 28
1778582480 28
1778582485 28
1778582490 28
1778582495 30
1778582500 30
1778582505 30
1778582510 30
```
</details>

---

