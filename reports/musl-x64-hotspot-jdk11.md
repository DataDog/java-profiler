---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:47:17 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 35-43 cores)</summary>

```
1795113793 35
1795113799 35
1795113804 35
1795113809 35
1795113814 35
1795113819 35
1795113824 35
1795113829 43
1795113834 43
1795113839 43
1795113844 43
1795113849 43
1795113854 43
1795113859 43
1795113864 43
1795113869 43
1795113874 43
1795113879 43
1795113884 43
1795113889 43
```
</details>

---

