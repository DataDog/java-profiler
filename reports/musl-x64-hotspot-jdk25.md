---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:46:29 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 59-65 cores)</summary>

```
1778582402 62
1778582407 62
1778582412 59
1778582417 59
1778582422 59
1778582427 59
1778582432 59
1778582437 59
1778582442 61
1778582447 61
1778582452 61
1778582457 61
1778582462 61
1778582467 61
1778582472 61
1778582477 61
1778582482 61
1778582487 61
1778582492 61
1778582497 61
```
</details>

---

