---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:27:56 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 9 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1794234161 22
1794234166 22
1794234171 22
1794234176 22
1794234181 22
1794234186 22
1794234191 22
1794234196 22
1794234201 22
1794234206 24
1794234211 24
1794234216 22
1794234221 22
1794234226 22
1794234231 22
1794234236 22
1794234241 22
1794234246 22
1794234251 22
1794234256 22
```
</details>

---

