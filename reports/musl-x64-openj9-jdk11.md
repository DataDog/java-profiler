---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:18:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 584 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795529682 78
1795529687 78
1795529692 78
1795529697 78
1795529702 78
1795529707 78
1795529712 78
1795529717 78
1795529722 78
1795529727 78
1795529732 78
1795529737 78
1795529742 78
1795529747 78
1795529752 78
1795529757 78
1795529762 76
1795529767 76
1795529772 76
1795529777 76
```
</details>

---

