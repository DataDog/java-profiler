---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:06:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 28-43 cores)</summary>

```
1777557726 38
1777557731 43
1777557736 43
1777557741 38
1777557746 38
1777557751 38
1777557756 38
1777557761 38
1777557766 38
1777557771 33
1777557776 33
1777557781 33
1777557786 33
1777557791 33
1777557796 33
1777557801 33
1777557806 33
1777557811 33
1777557816 33
1777557821 33
```
</details>

---

