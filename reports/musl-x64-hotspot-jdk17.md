---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:38:23 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 33-45 cores)</summary>

```
1795001559 33
1795001564 43
1795001569 43
1795001574 43
1795001579 43
1795001584 43
1795001589 43
1795001594 43
1795001599 43
1795001604 43
1795001609 43
1795001614 43
1795001619 43
1795001624 43
1795001629 43
1795001634 43
1795001639 43
1795001644 43
1795001650 43
1795001655 43
```
</details>

---

