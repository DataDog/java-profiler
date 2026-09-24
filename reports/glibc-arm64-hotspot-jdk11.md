---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:24:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 12 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790241520 46
1790241525 46
1790241530 46
1790241535 46
1790241540 46
1790241545 46
1790241550 46
1790241555 46
1790241560 46
1790241565 46
1790241570 48
1790241575 48
1790241580 48
1790241585 48
1790241590 48
1790241595 48
1790241600 48
1790241605 43
1790241610 43
1790241615 43
```
</details>

---

