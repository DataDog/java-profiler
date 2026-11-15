---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 14:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 7 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1794770909 19
1794770914 19
1794770919 19
1794770924 19
1794770929 19
1794770934 19
1794770939 24
1794770944 24
1794770949 24
1794770955 24
1794770960 24
1794770965 24
1794770970 24
1794770975 24
1794770980 24
1794770985 24
1794770990 24
1794770995 24
1794771000 24
1794771005 24
```
</details>

---

