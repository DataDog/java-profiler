---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:31:48 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794824769 80
1794824774 80
1794824779 80
1794824784 80
1794824789 80
1794824794 82
1794824799 82
1794824804 82
1794824809 82
1794824814 82
1794824819 82
1794824824 82
1794824829 82
1794824834 80
1794824839 80
1794824844 80
1794824849 80
1794824854 80
1794824859 80
1794824864 80
```
</details>

---

