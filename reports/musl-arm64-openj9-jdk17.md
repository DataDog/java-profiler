---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:56:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 8 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794325879 48
1794325884 48
1794325889 36
1794325894 36
1794325899 36
1794325904 36
1794325909 36
1794325914 36
1794325919 36
1794325924 36
1794325929 36
1794325934 36
1794325939 36
1794325944 36
1794325949 36
1794325954 36
1794325959 36
1794325964 36
1794325969 36
1794325974 36
```
</details>

---

