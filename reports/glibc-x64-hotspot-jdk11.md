---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 05:44:47 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1791538761 11
1791538766 11
1791538771 11
1791538776 11
1791538781 11
1791538786 11
1791538791 11
1791538796 11
1791538801 11
1791538806 11
1791538811 11
1791538816 11
1791538821 32
1791538826 32
1791538831 11
1791538836 11
1791538841 11
1791538846 11
1791538851 11
1791538856 11
```
</details>

---

