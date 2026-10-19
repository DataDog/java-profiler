---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 01:06:11 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1792386177 37
1792386182 48
1792386187 48
1792386192 48
1792386197 48
1792386202 43
1792386207 43
1792386212 43
1792386217 43
1792386222 43
1792386227 43
1792386232 43
1792386237 43
1792386242 43
1792386247 43
1792386252 43
1792386257 43
1792386262 43
1792386267 43
1792386272 43
```
</details>

---

