---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1793829481 43
1793829486 43
1793829491 43
1793829496 43
1793829501 43
1793829506 43
1793829511 43
1793829516 43
1793829521 43
1793829526 43
1793829531 45
1793829536 45
1793829541 43
1793829546 43
1793829551 43
1793829556 43
1793829561 43
1793829566 43
1793829571 43
1793829576 43
```
</details>

---

