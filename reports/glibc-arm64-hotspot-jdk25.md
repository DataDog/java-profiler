---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:03:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 11 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789682207 31
1789682212 31
1789682217 31
1789682222 31
1789682227 31
1789682232 31
1789682237 31
1789682242 31
1789682247 31
1789682252 31
1789682257 26
1789682262 26
1789682267 26
1789682272 26
1789682277 26
1789682282 26
1789682287 26
1789682292 26
1789682297 26
1789682302 26
```
</details>

---

