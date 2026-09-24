---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 15:41:52 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790278656 50
1790278661 50
1790278666 50
1790278671 50
1790278676 50
1790278681 50
1790278686 50
1790278691 50
1790278696 50
1790278701 50
1790278706 50
1790278711 50
1790278716 50
1790278721 50
1790278726 50
1790278731 50
1790278736 50
1790278741 50
1790278746 50
1790278751 50
```
</details>

---

