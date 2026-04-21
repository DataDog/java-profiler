---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-21 13:54:23 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1019 |
| Sample Rate | 16.98/sec |
| Health Score | 1061% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1776793769 60
1776793774 60
1776793779 60
1776793784 60
1776793789 60
1776793794 60
1776793799 60
1776793804 60
1776793809 60
1776793814 60
1776793819 60
1776793824 60
1776793829 60
1776793834 60
1776793839 58
1776793844 58
1776793849 58
1776793855 58
1776793860 58
1776793865 58
```
</details>

---

