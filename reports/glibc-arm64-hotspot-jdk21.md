---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:37 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793203201 51
1793203206 51
1793203211 51
1793203216 51
1793203221 51
1793203226 51
1793203231 51
1793203236 51
1793203241 51
1793203246 51
1793203251 51
1793203256 46
1793203261 46
1793203266 46
1793203271 46
1793203276 46
1793203281 46
1793203286 46
1793203291 46
1793203296 46
```
</details>

---

