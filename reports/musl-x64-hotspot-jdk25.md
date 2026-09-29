---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 16-32 cores)</summary>

```
1790699287 32
1790699292 32
1790699297 32
1790699302 32
1790699307 32
1790699312 32
1790699317 32
1790699322 32
1790699327 32
1790699332 32
1790699337 32
1790699342 32
1790699347 32
1790699352 32
1790699357 32
1790699362 32
1790699367 32
1790699372 32
1790699377 32
1790699382 32
```
</details>

---

