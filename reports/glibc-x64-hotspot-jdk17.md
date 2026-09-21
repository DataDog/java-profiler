---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 03:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 33-74 cores)</summary>

```
1789975457 33
1789975462 33
1789975467 33
1789975472 33
1789975477 33
1789975482 33
1789975487 33
1789975492 33
1789975497 33
1789975502 33
1789975507 33
1789975512 33
1789975517 33
1789975522 33
1789975527 33
1789975532 33
1789975537 33
1789975542 74
1789975547 74
1789975552 74
```
</details>

---

