---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1790604686 48
1790604691 48
1790604696 48
1790604701 48
1790604706 48
1790604711 48
1790604716 44
1790604721 44
1790604726 44
1790604731 44
1790604736 44
1790604741 44
1790604746 44
1790604751 44
1790604756 44
1790604761 44
1790604766 44
1790604771 44
1790604776 44
1790604781 44
```
</details>

---

