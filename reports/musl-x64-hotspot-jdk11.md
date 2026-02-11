---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:58:27 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (4 unique values: 45-66 cores)</summary>

```
1770828687 45
1770828692 55
1770828697 55
1770828702 55
1770828707 46
1770828712 46
1770828717 46
1770828722 46
1770828727 46
1770828732 46
1770828737 66
1770828742 66
1770828747 66
1770828752 66
1770828757 66
1770828762 66
1770828767 66
1770828772 66
1770828777 66
1770828782 66
```
</details>

---

