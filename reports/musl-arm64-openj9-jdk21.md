---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:52:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790174755 50
1790174760 50
1790174765 50
1790174770 50
1790174775 50
1790174780 50
1790174785 50
1790174791 50
1790174796 50
1790174801 50
1790174806 50
1790174811 50
1790174816 50
1790174821 50
1790174826 50
1790174831 50
1790174836 50
1790174841 50
1790174846 50
1790174851 50
```
</details>

---

