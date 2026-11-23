---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-67 cores)</summary>

```
1795434610 67
1795434615 65
1795434620 65
1795434625 65
1795434630 65
1795434635 65
1795434640 65
1795434645 65
1795434650 65
1795434655 67
1795434660 67
1795434665 47
1795434670 47
1795434675 47
1795434681 47
1795434686 47
1795434691 47
1795434696 47
1795434701 47
1795434706 47
```
</details>

---

