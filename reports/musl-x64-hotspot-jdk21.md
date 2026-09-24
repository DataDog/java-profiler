---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 15:41:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 51-88 cores)</summary>

```
1790278653 60
1790278658 60
1790278663 52
1790278668 52
1790278673 52
1790278678 88
1790278683 88
1790278688 51
1790278693 51
1790278698 51
1790278703 51
1790278708 51
1790278713 51
1790278718 51
1790278723 51
1790278728 51
1790278733 51
1790278738 51
1790278743 51
1790278748 51
```
</details>

---

