---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:14:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795108193 50
1795108198 50
1795108203 50
1795108208 50
1795108213 50
1795108218 50
1795108223 50
1795108228 50
1795108233 50
1795108238 50
1795108243 50
1795108248 50
1795108253 50
1795108258 50
1795108263 50
1795108268 50
1795108273 50
1795108278 50
1795108283 50
1795108288 50
```
</details>

---

