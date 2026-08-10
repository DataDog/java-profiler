---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:46:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 66-73 cores)</summary>

```
1786376441 73
1786376446 73
1786376451 73
1786376456 73
1786376461 73
1786376466 73
1786376471 73
1786376476 68
1786376481 68
1786376486 68
1786376491 68
1786376496 68
1786376501 68
1786376506 68
1786376511 68
1786376516 68
1786376521 68
1786376526 66
1786376531 66
1786376536 66
```
</details>

---

