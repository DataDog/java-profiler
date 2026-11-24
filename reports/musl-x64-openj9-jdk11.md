---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 11 |
| Allocations | 573 |

<details>
<summary>CPU Timeline (2 unique values: 31-57 cores)</summary>

```
1795496405 57
1795496410 31
1795496415 31
1795496420 31
1795496425 31
1795496430 31
1795496435 31
1795496440 31
1795496445 31
1795496450 31
1795496455 31
1795496460 31
1795496465 31
1795496470 31
1795496475 31
1795496480 31
1795496485 31
1795496490 31
1795496495 31
1795496500 31
```
</details>

---

