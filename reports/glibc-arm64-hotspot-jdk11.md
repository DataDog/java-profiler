---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-06-10 05:13:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1028 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1781082624 48
1781082629 48
1781082634 48
1781082639 48
1781082644 48
1781082649 43
1781082654 43
1781082659 43
1781082664 38
1781082669 38
1781082674 42
1781082679 42
1781082684 42
1781082689 42
1781082694 42
1781082699 42
1781082704 42
1781082709 42
1781082714 42
1781082719 42
```
</details>

---

