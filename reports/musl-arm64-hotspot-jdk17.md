---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-16 12:11:37 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1789574760 14
1789574765 14
1789574770 14
1789574775 14
1789574780 14
1789574785 14
1789574790 14
1789574795 14
1789574800 14
1789574805 14
1789574810 14
1789574815 14
1789574820 14
1789574825 14
1789574830 14
1789574835 14
1789574840 14
1789574845 16
1789574850 16
1789574855 16
```
</details>

---

