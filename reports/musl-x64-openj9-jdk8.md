---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 11:39:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 84-92 cores)</summary>

```
1795537826 92
1795537831 92
1795537836 92
1795537841 92
1795537846 92
1795537851 92
1795537856 92
1795537861 84
1795537866 84
1795537871 84
1795537876 84
1795537881 84
1795537886 84
1795537891 84
1795537896 84
1795537901 86
1795537906 86
1795537911 86
1795537916 86
1795537921 86
```
</details>

---

