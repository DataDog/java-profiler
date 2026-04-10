---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-10 14:16:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1120 |
| Sample Rate | 18.67/sec |
| Health Score | 1167% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1775844597 27
1775844602 27
1775844607 27
1775844612 27
1775844617 27
1775844622 22
1775844627 22
1775844632 22
1775844637 22
1775844642 22
1775844647 22
1775844652 22
1775844657 22
1775844662 22
1775844667 22
1775844672 22
1775844678 22
1775844683 22
1775844688 22
1775844693 22
```
</details>

---

