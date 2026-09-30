---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 10:44:04 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 12 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790779178 43
1790779183 48
1790779188 48
1790779194 48
1790779199 48
1790779204 48
1790779209 48
1790779214 48
1790779219 48
1790779224 48
1790779229 48
1790779234 48
1790779239 48
1790779244 48
1790779249 48
1790779254 48
1790779259 48
1790779264 48
1790779269 48
1790779274 48
```
</details>

---

