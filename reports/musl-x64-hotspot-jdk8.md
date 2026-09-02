---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-02 09:19:24 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 65-79 cores)</summary>

```
1788354651 65
1788354656 65
1788354661 65
1788354666 65
1788354671 65
1788354676 67
1788354681 67
1788354686 67
1788354691 67
1788354696 67
1788354701 67
1788354706 67
1788354711 67
1788354717 67
1788354722 67
1788354727 67
1788354732 79
1788354737 79
1788354742 79
1788354747 79
```
</details>

---

