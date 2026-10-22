---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:01:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 39-68 cores)</summary>

```
1792670172 39
1792670177 39
1792670182 39
1792670187 39
1792670192 39
1792670197 39
1792670202 56
1792670207 56
1792670212 56
1792670217 56
1792670222 56
1792670227 56
1792670232 56
1792670237 56
1792670242 56
1792670247 56
1792670252 56
1792670258 56
1792670263 56
1792670268 56
```
</details>

---

