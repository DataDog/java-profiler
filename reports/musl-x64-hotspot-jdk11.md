---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 15:41:52 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 69-79 cores)</summary>

```
1790278631 70
1790278636 70
1790278641 70
1790278646 70
1790278651 70
1790278656 70
1790278661 70
1790278666 70
1790278671 70
1790278676 70
1790278681 79
1790278686 79
1790278691 69
1790278696 69
1790278701 69
1790278706 69
1790278711 69
1790278716 69
1790278721 69
1790278726 69
```
</details>

---

