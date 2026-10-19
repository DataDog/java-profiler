---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:28:18 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 42-82 cores)</summary>

```
1792372990 42
1792372995 42
1792373000 42
1792373005 42
1792373011 42
1792373016 42
1792373021 42
1792373026 42
1792373031 42
1792373036 42
1792373041 62
1792373046 62
1792373051 62
1792373056 62
1792373061 62
1792373066 62
1792373071 62
1792373076 62
1792373081 82
1792373086 82
```
</details>

---

