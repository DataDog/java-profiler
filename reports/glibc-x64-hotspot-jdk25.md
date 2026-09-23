---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 05:40:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1790156117 47
1790156122 47
1790156127 47
1790156132 47
1790156137 47
1790156142 47
1790156147 47
1790156152 47
1790156157 47
1790156162 47
1790156167 45
1790156172 45
1790156177 45
1790156182 45
1790156187 45
1790156192 45
1790156197 47
1790156202 47
1790156207 47
1790156212 47
```
</details>

---

