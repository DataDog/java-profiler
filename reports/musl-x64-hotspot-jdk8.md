---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-57 cores)</summary>

```
1777983461 57
1777983466 57
1777983471 57
1777983476 57
1777983481 57
1777983486 52
1777983491 52
1777983496 52
1777983501 52
1777983506 52
1777983511 52
1777983516 52
1777983521 52
1777983526 52
1777983531 47
1777983536 47
1777983541 47
1777983546 47
1777983551 47
1777983556 47
```
</details>

---

