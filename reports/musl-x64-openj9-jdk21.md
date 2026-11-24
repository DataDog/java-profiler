---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 11:39:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 64-79 cores)</summary>

```
1795537828 64
1795537833 64
1795537838 75
1795537843 75
1795537848 75
1795537853 75
1795537858 75
1795537863 77
1795537868 77
1795537873 79
1795537878 79
1795537883 79
1795537888 79
1795537893 79
1795537898 79
1795537903 79
1795537908 79
1795537913 79
1795537918 79
1795537923 79
```
</details>

---

