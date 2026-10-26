---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 00:55:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1792990167 43
1792990172 43
1792990177 43
1792990182 43
1792990187 43
1792990192 43
1792990197 38
1792990202 38
1792990207 38
1792990212 38
1792990217 38
1792990222 38
1792990227 38
1792990232 38
1792990237 38
1792990242 38
1792990247 38
1792990252 38
1792990257 38
1792990262 38
```
</details>

---

