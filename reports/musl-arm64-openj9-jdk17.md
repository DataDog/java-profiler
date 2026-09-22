---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 15:04:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 10 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (4 unique values: 44-64 cores)</summary>

```
1790103632 49
1790103637 49
1790103642 49
1790103647 49
1790103652 49
1790103657 44
1790103662 44
1790103667 44
1790103672 44
1790103677 44
1790103682 44
1790103687 44
1790103692 44
1790103697 49
1790103702 49
1790103707 64
1790103712 64
1790103717 50
1790103722 50
1790103727 50
```
</details>

---

