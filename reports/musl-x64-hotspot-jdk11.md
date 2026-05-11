---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 18:32:12 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1778538426 87
1778538431 87
1778538436 87
1778538441 87
1778538446 87
1778538451 87
1778538456 87
1778538461 87
1778538466 87
1778538471 91
1778538476 91
1778538481 91
1778538486 91
1778538491 91
1778538496 91
1778538501 89
1778538506 89
1778538511 89
1778538516 91
1778538521 91
```
</details>

---

