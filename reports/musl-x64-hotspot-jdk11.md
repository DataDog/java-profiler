---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:20 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1064 |
| Sample Rate | 17.73/sec |
| Health Score | 1108% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 54-57 cores)</summary>

```
1777235467 57
1777235472 57
1777235477 54
1777235482 54
1777235487 54
1777235492 54
1777235497 54
1777235502 54
1777235507 54
1777235512 54
1777235517 54
1777235522 54
1777235527 54
1777235532 54
1777235537 54
1777235542 54
1777235547 54
1777235552 54
1777235558 54
1777235563 54
```
</details>

---

