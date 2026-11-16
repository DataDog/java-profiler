---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:52:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 73-79 cores)</summary>

```
1794836798 79
1794836803 79
1794836808 79
1794836813 79
1794836818 79
1794836823 79
1794836828 79
1794836833 79
1794836838 79
1794836843 79
1794836848 79
1794836853 79
1794836858 79
1794836863 77
1794836868 77
1794836873 77
1794836878 75
1794836883 75
1794836888 75
1794836893 75
```
</details>

---

