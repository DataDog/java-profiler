---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 09:13:21 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 10 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1792156118 35
1792156123 35
1792156128 35
1792156133 35
1792156138 40
1792156143 40
1792156148 40
1792156153 40
1792156158 40
1792156163 40
1792156168 40
1792156173 40
1792156178 40
1792156183 40
1792156188 40
1792156193 40
1792156198 40
1792156203 40
1792156208 40
1792156213 40
```
</details>

---

