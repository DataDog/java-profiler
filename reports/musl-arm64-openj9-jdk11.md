---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:36:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1795001539 64
1795001544 64
1795001549 64
1795001554 64
1795001559 64
1795001564 64
1795001569 64
1795001574 64
1795001579 64
1795001584 64
1795001589 64
1795001594 64
1795001599 64
1795001604 64
1795001609 64
1795001614 64
1795001619 64
1795001624 64
1795001629 64
1795001634 64
```
</details>

---

