---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:34:16 EDT

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
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790094183 50
1790094188 50
1790094193 50
1790094198 50
1790094203 50
1790094208 50
1790094213 50
1790094219 50
1790094224 50
1790094229 50
1790094234 50
1790094239 50
1790094244 50
1790094249 50
1790094254 50
1790094259 50
1790094264 50
1790094269 50
1790094274 50
1790094279 50
```
</details>

---

