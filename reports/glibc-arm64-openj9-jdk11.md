---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 03:36:29 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790580761 48
1790580766 48
1790580771 48
1790580776 48
1790580781 48
1790580786 48
1790580791 48
1790580796 48
1790580801 48
1790580806 48
1790580811 48
1790580816 48
1790580821 48
1790580826 48
1790580831 48
1790580836 48
1790580841 48
1790580846 48
1790580851 48
1790580856 48
```
</details>

---

