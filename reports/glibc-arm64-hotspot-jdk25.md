---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 09:54:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 49-50 cores)</summary>

```
1790257801 50
1790257806 50
1790257811 50
1790257816 50
1790257821 50
1790257826 50
1790257831 50
1790257836 50
1790257841 50
1790257846 50
1790257851 50
1790257856 50
1790257861 50
1790257866 50
1790257871 50
1790257876 50
1790257881 50
1790257886 50
1790257891 50
1790257896 50
```
</details>

---

