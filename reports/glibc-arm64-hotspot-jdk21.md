---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:52:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 22-50 cores)</summary>

```
1790174790 22
1790174795 22
1790174800 22
1790174805 22
1790174810 22
1790174815 22
1790174820 22
1790174825 22
1790174830 22
1790174835 22
1790174840 22
1790174845 36
1790174850 36
1790174855 36
1790174860 36
1790174865 50
1790174870 50
1790174875 50
1790174880 50
1790174885 50
```
</details>

---

