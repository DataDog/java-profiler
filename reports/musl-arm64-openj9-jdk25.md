---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 12:40:12 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1791995793 46
1791995798 46
1791995803 46
1791995808 46
1791995813 46
1791995818 46
1791995823 51
1791995828 51
1791995833 51
1791995838 51
1791995843 51
1791995848 51
1791995853 51
1791995858 51
1791995863 51
1791995868 51
1791995873 51
1791995878 64
1791995883 64
1791995888 64
```
</details>

---

