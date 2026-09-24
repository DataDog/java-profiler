---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 10:20:19 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 8 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790259178 32
1790259183 32
1790259188 32
1790259193 32
1790259198 32
1790259203 32
1790259208 32
1790259213 32
1790259218 32
1790259223 32
1790259228 32
1790259233 32
1790259238 32
1790259243 32
1790259248 32
1790259253 32
1790259258 32
1790259263 32
1790259268 32
1790259273 32
```
</details>

---

