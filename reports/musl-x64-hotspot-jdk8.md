---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 53-74 cores)</summary>

```
1790172257 53
1790172262 53
1790172267 53
1790172272 53
1790172277 53
1790172282 53
1790172287 53
1790172292 74
1790172297 74
1790172302 69
1790172307 69
1790172312 69
1790172317 69
1790172322 67
1790172327 67
1790172332 67
1790172337 67
1790172342 67
1790172347 67
1790172352 67
```
</details>

---

