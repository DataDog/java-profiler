---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 15:41:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1790278636 96
1790278641 96
1790278646 96
1790278651 96
1790278656 96
1790278661 96
1790278666 96
1790278671 96
1790278676 96
1790278681 96
1790278686 82
1790278691 82
1790278696 82
1790278701 74
1790278706 74
1790278711 74
1790278716 74
1790278721 74
1790278726 74
1790278731 74
```
</details>

---

