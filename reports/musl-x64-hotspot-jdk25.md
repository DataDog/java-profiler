---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 16:03:20 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 50-74 cores)</summary>

```
1790193522 74
1790193527 74
1790193532 70
1790193537 70
1790193542 70
1790193547 70
1790193552 70
1790193557 70
1790193562 70
1790193567 70
1790193572 70
1790193577 70
1790193582 70
1790193587 70
1790193592 70
1790193597 70
1790193602 70
1790193607 70
1790193612 70
1790193617 70
```
</details>

---

