---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 19:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 35-43 cores)</summary>

```
1792712232 43
1792712237 43
1792712242 43
1792712247 43
1792712252 43
1792712257 43
1792712262 43
1792712267 43
1792712272 43
1792712277 43
1792712282 43
1792712287 43
1792712292 43
1792712297 43
1792712302 43
1792712307 43
1792712312 35
1792712317 35
1792712322 35
1792712327 35
```
</details>

---

