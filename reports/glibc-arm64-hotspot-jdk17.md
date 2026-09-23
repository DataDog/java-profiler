---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:08:36 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790172168 43
1790172173 43
1790172178 43
1790172183 43
1790172188 43
1790172193 48
1790172198 48
1790172203 48
1790172208 48
1790172213 48
1790172218 48
1790172223 48
1790172228 48
1790172233 48
1790172238 48
1790172243 48
1790172248 48
1790172253 48
1790172258 48
1790172263 48
```
</details>

---

