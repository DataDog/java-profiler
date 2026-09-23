---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 05:40:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790156128 50
1790156133 50
1790156138 50
1790156143 50
1790156148 50
1790156153 50
1790156158 50
1790156163 50
1790156168 50
1790156173 50
1790156178 50
1790156183 50
1790156188 50
1790156193 50
1790156198 50
1790156203 50
1790156208 50
1790156213 50
1790156218 50
1790156223 50
```
</details>

---

