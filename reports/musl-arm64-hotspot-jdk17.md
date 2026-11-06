---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 15:13:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 14 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793995727 51
1793995732 51
1793995737 51
1793995742 51
1793995747 51
1793995752 51
1793995757 51
1793995762 51
1793995767 51
1793995772 51
1793995777 51
1793995782 51
1793995787 51
1793995792 51
1793995797 51
1793995802 51
1793995807 51
1793995812 51
1793995817 51
1793995822 51
```
</details>

---

