---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1790604750 44
1790604755 44
1790604760 44
1790604765 44
1790604771 44
1790604776 44
1790604781 44
1790604786 44
1790604791 44
1790604796 44
1790604801 44
1790604806 48
1790604811 48
1790604816 48
1790604821 48
1790604826 48
1790604831 48
1790604836 48
1790604841 48
1790604846 48
```
</details>

---

