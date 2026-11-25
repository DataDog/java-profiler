---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 05:53:54 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1083 |
| Sample Rate | 18.05/sec |
| Health Score | 1128% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795603749 72
1795603754 72
1795603759 72
1795603764 72
1795603769 70
1795603774 70
1795603779 70
1795603784 70
1795603789 70
1795603794 70
1795603799 70
1795603804 70
1795603809 70
1795603814 70
1795603819 70
1795603824 70
1795603829 70
1795603834 70
1795603839 70
1795603845 70
```
</details>

---

