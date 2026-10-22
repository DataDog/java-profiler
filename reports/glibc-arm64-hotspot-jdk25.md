---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 19:06:01 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792710168 46
1792710173 46
1792710178 46
1792710183 46
1792710188 46
1792710193 46
1792710198 46
1792710203 46
1792710208 46
1792710213 51
1792710218 51
1792710223 51
1792710228 51
1792710233 51
1792710238 51
1792710243 51
1792710248 51
1792710253 51
1792710258 51
1792710263 51
```
</details>

---

