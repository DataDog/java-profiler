---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 12:33:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 13 |
| Allocations | 184 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1790699302 40
1790699307 40
1790699312 42
1790699317 42
1790699322 42
1790699327 42
1790699332 42
1790699337 42
1790699342 42
1790699347 42
1790699352 42
1790699357 42
1790699362 43
1790699367 43
1790699372 43
1790699377 43
1790699382 43
1790699387 43
1790699392 43
1790699397 43
```
</details>

---

