---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 00:55:16 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 14 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 17-18 cores)</summary>

```
1792990163 17
1792990168 17
1792990173 17
1792990178 17
1792990183 17
1792990188 17
1792990193 17
1792990198 17
1792990203 17
1792990208 17
1792990213 18
1792990218 18
1792990223 18
1792990228 18
1792990233 18
1792990238 18
1792990243 18
1792990248 18
1792990253 18
1792990258 18
```
</details>

---

