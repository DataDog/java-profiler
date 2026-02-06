---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-06 09:56:51 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770389502 32
1770389507 32
1770389512 32
1770389517 32
1770389522 32
1770389527 29
1770389532 29
1770389537 29
1770389542 29
1770389547 29
1770389552 29
1770389557 29
1770389562 29
1770389567 29
1770389573 29
1770389578 29
1770389583 29
1770389588 29
1770389593 29
1770389598 29
```
</details>

---

