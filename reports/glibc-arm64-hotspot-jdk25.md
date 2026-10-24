---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-24 05:55:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 12 |
| Allocations | 121 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 49-56 cores)</summary>

```
1792835517 56
1792835522 56
1792835527 56
1792835532 56
1792835537 56
1792835542 56
1792835547 56
1792835552 56
1792835557 56
1792835562 56
1792835567 49
1792835572 49
1792835577 49
1792835582 49
1792835587 49
1792835592 49
1792835597 49
1792835602 49
1792835607 49
1792835612 49
```
</details>

---

