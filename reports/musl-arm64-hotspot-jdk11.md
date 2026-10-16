---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 09:30:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 12 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792157124 46
1792157129 46
1792157134 48
1792157139 48
1792157144 48
1792157149 48
1792157154 48
1792157159 48
1792157164 48
1792157169 48
1792157174 48
1792157179 48
1792157184 48
1792157189 48
1792157194 48
1792157199 48
1792157204 48
1792157209 48
1792157214 48
1792157219 48
```
</details>

---

