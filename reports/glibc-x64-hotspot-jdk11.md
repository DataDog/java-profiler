---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 12:27:25 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 7-15 cores)</summary>

```
1790094009 7
1790094014 7
1790094019 7
1790094024 7
1790094029 7
1790094034 7
1790094039 15
1790094044 15
1790094049 15
1790094054 15
1790094059 15
1790094064 15
1790094069 15
1790094074 15
1790094079 15
1790094084 15
1790094089 15
1790094094 15
1790094099 15
1790094104 15
```
</details>

---

