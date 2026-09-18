---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 02:28:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789712640 45
1789712645 45
1789712650 45
1789712655 45
1789712660 45
1789712665 45
1789712670 45
1789712675 45
1789712680 45
1789712685 45
1789712690 45
1789712695 48
1789712700 48
1789712705 48
1789712710 48
1789712715 48
1789712720 48
1789712725 48
1789712731 48
1789712736 48
```
</details>

---

