---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 06:31:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 46-58 cores)</summary>

```
1790850398 46
1790850403 46
1790850408 46
1790850413 46
1790850418 46
1790850423 46
1790850428 46
1790850433 46
1790850438 46
1790850443 46
1790850448 46
1790850453 46
1790850458 46
1790850463 46
1790850468 58
1790850473 58
1790850478 58
1790850483 58
1790850488 58
1790850493 58
```
</details>

---

