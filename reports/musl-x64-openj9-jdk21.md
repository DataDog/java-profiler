---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 14:32:55 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 14.70/sec |
| Health Score | 919% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1794770924 28
1794770929 28
1794770934 28
1794770939 28
1794770944 28
1794770949 28
1794770954 28
1794770959 28
1794770964 28
1794770969 28
1794770974 28
1794770979 26
1794770984 26
1794770989 26
1794770994 26
1794770999 26
1794771004 26
1794771009 28
1794771014 28
1794771019 28
```
</details>

---

