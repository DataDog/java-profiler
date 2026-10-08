---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:10:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1791468204 80
1791468209 80
1791468214 80
1791468219 80
1791468224 82
1791468229 82
1791468234 82
1791468239 82
1791468244 82
1791468249 84
1791468254 84
1791468260 84
1791468265 82
1791468270 82
1791468275 84
1791468280 84
1791468285 84
1791468290 84
1791468295 84
1791468300 84
```
</details>

---

