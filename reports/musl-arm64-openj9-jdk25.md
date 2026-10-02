---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-02 14:02:19 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790963885 47
1790963890 47
1790963895 47
1790963900 47
1790963905 47
1790963910 48
1790963915 48
1790963920 48
1790963925 43
1790963930 43
1790963935 43
1790963940 43
1790963945 43
1790963950 43
1790963955 43
1790963960 43
1790963965 43
1790963970 43
1790963975 43
1790963980 43
```
</details>

---

