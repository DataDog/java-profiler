---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 08:01:22 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790596527 43
1790596532 43
1790596537 43
1790596542 38
1790596547 38
1790596552 38
1790596557 38
1790596562 38
1790596567 38
1790596572 38
1790596577 38
1790596582 38
1790596587 38
1790596592 38
1790596597 38
1790596602 38
1790596607 38
1790596612 38
1790596617 38
1790596622 38
```
</details>

---

