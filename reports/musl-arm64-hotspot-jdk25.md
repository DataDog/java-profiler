---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790172183 48
1790172188 48
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
1790172243 46
1790172248 46
1790172253 46
1790172258 46
1790172263 46
1790172268 46
1790172273 46
1790172278 46
```
</details>

---

