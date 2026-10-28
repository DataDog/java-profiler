---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 01:05:56 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 26-46 cores)</summary>

```
1793163616 46
1793163621 46
1793163626 46
1793163631 46
1793163636 46
1793163641 26
1793163646 26
1793163651 26
1793163656 26
1793163661 26
1793163666 26
1793163671 26
1793163676 26
1793163681 26
1793163686 26
1793163691 26
1793163696 26
1793163701 26
1793163706 26
1793163711 26
```
</details>

---

