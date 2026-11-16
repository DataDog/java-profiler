---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 08:52:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794836788 51
1794836793 51
1794836798 51
1794836803 51
1794836808 51
1794836813 49
1794836818 49
1794836823 49
1794836828 49
1794836833 49
1794836838 49
1794836843 49
1794836848 49
1794836853 49
1794836858 49
1794836863 51
1794836868 51
1794836873 51
1794836878 51
1794836883 51
```
</details>

---

