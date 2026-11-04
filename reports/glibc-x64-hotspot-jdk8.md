---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793829475 40
1793829480 40
1793829485 40
1793829490 40
1793829495 40
1793829500 40
1793829505 40
1793829510 40
1793829515 40
1793829521 40
1793829526 40
1793829531 40
1793829536 40
1793829541 40
1793829546 40
1793829551 40
1793829556 40
1793829561 40
1793829566 40
1793829571 40
```
</details>

---

