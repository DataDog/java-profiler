---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-10 12:11:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1775837221 43
1775837226 43
1775837231 43
1775837236 43
1775837241 38
1775837246 38
1775837251 38
1775837256 38
1775837261 38
1775837266 38
1775837271 38
1775837276 38
1775837281 38
1775837286 38
1775837291 38
1775837296 38
1775837301 38
1775837306 38
1775837311 38
1775837316 38
```
</details>

---

