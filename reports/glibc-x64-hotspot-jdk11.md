---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 14:20:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 76-81 cores)</summary>

```
1792520019 81
1792520024 81
1792520029 81
1792520034 76
1792520039 76
1792520044 76
1792520049 76
1792520055 76
1792520060 81
1792520065 81
1792520070 79
1792520075 79
1792520080 77
1792520085 77
1792520090 77
1792520095 77
1792520100 77
1792520105 77
1792520110 77
1792520115 77
```
</details>

---

