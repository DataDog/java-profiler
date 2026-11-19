---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 15:50:36 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795121188 50
1795121193 50
1795121198 50
1795121203 50
1795121208 50
1795121213 50
1795121218 50
1795121223 50
1795121228 50
1795121233 50
1795121238 50
1795121243 50
1795121248 50
1795121253 50
1795121258 50
1795121263 50
1795121268 50
1795121273 50
1795121278 50
1795121283 50
```
</details>

---

