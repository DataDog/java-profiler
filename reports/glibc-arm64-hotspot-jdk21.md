---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:01:47 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1792670247 30
1792670252 30
1792670257 30
1792670262 30
1792670267 35
1792670272 35
1792670277 30
1792670282 30
1792670287 30
1792670292 30
1792670297 30
1792670302 30
1792670307 30
1792670312 30
1792670317 30
1792670322 30
1792670327 35
1792670332 35
1792670337 30
1792670342 30
```
</details>

---

