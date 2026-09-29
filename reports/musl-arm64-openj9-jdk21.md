---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1790699312 41
1790699317 41
1790699322 41
1790699327 41
1790699332 41
1790699337 41
1790699342 41
1790699347 41
1790699352 41
1790699357 41
1790699362 43
1790699367 43
1790699372 43
1790699377 43
1790699382 43
1790699387 43
1790699392 43
1790699397 43
1790699402 43
1790699407 43
```
</details>

---

