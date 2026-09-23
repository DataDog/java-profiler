---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 9 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 12 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1790174736 36
1790174741 36
1790174746 36
1790174751 36
1790174756 36
1790174761 36
1790174766 36
1790174771 36
1790174776 36
1790174781 36
1790174786 36
1790174791 36
1790174796 36
1790174801 36
1790174806 36
1790174811 36
1790174816 36
1790174821 36
1790174826 36
1790174831 36
```
</details>

---

