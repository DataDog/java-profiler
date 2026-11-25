---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:49:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 10 |
| Allocations | 34 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 35-44 cores)</summary>

```
1795621546 44
1795621551 44
1795621556 44
1795621561 44
1795621566 44
1795621571 35
1795621576 35
1795621581 35
1795621586 35
1795621591 35
1795621596 35
1795621601 35
1795621607 35
1795621612 35
1795621617 35
1795621622 35
1795621627 35
1795621632 35
1795621637 35
1795621642 35
```
</details>

---

