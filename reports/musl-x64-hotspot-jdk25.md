---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:26:21 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 11 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 75-96 cores)</summary>

```
1794572476 75
1794572481 96
1794572486 96
1794572491 96
1794572496 96
1794572501 96
1794572506 96
1794572511 96
1794572516 96
1794572521 96
1794572526 96
1794572531 96
1794572536 96
1794572541 96
1794572546 96
1794572551 96
1794572556 96
1794572561 96
1794572566 96
1794572571 96
```
</details>

---

