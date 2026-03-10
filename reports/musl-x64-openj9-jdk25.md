---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:55:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 13 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 80-96 cores)</summary>

```
1773164995 80
1773165000 82
1773165005 82
1773165010 82
1773165015 82
1773165020 82
1773165025 82
1773165030 84
1773165035 84
1773165040 84
1773165045 84
1773165050 84
1773165055 84
1773165060 84
1773165065 84
1773165070 84
1773165075 84
1773165080 84
1773165085 94
1773165090 94
```
</details>

---

