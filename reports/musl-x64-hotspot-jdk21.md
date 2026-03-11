---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 13:17:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 12 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 28-36 cores)</summary>

```
1773249100 28
1773249105 28
1773249110 32
1773249115 32
1773249120 32
1773249125 32
1773249130 32
1773249135 32
1773249140 32
1773249145 32
1773249150 32
1773249155 32
1773249160 32
1773249165 32
1773249170 32
1773249175 32
1773249180 32
1773249185 32
1773249190 32
1773249195 32
```
</details>

---

