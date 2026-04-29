---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 61-74 cores)</summary>

```
1777462482 63
1777462487 63
1777462492 63
1777462497 63
1777462502 63
1777462507 63
1777462512 61
1777462517 61
1777462522 61
1777462527 62
1777462532 62
1777462537 62
1777462542 70
1777462547 70
1777462552 70
1777462557 74
1777462562 74
1777462567 74
1777462572 74
1777462577 74
```
</details>

---

