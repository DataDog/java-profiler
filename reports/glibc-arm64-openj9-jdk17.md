---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 17:43:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 11-48 cores)</summary>

```
1790026751 11
1790026756 11
1790026761 11
1790026766 11
1790026771 11
1790026776 11
1790026781 11
1790026786 11
1790026791 11
1790026796 11
1790026801 11
1790026806 11
1790026811 48
1790026816 48
1790026821 48
1790026826 48
1790026831 11
1790026836 11
1790026841 11
1790026846 11
```
</details>

---

