---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 60-76 cores)</summary>

```
1770130551 60
1770130556 60
1770130561 60
1770130566 60
1770130571 60
1770130576 60
1770130581 60
1770130586 60
1770130592 60
1770130597 60
1770130602 65
1770130607 65
1770130612 74
1770130617 74
1770130622 76
1770130627 76
1770130632 76
1770130637 76
1770130642 76
1770130647 76
```
</details>

---

