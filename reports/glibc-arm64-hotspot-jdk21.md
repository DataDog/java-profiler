---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 09:30:24 EDT

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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792157183 43
1792157188 43
1792157193 43
1792157198 43
1792157203 43
1792157208 43
1792157213 43
1792157218 43
1792157223 43
1792157228 48
1792157233 48
1792157238 48
1792157243 48
1792157248 48
1792157253 48
1792157258 48
1792157263 48
1792157268 48
1792157273 48
1792157278 48
```
</details>

---

