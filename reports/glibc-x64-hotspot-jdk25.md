---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:10:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 58-69 cores)</summary>

```
1791468216 63
1791468221 63
1791468226 63
1791468231 63
1791468236 63
1791468241 63
1791468246 63
1791468251 63
1791468256 63
1791468261 63
1791468266 63
1791468271 58
1791468276 58
1791468281 58
1791468286 58
1791468291 58
1791468296 58
1791468301 69
1791468306 69
1791468311 69
```
</details>

---

