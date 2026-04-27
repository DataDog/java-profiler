---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 27-30 cores)</summary>

```
1777280984 27
1777280989 27
1777280994 29
1777280999 29
1777281004 29
1777281009 29
1777281014 29
1777281019 29
1777281024 30
1777281029 30
1777281034 30
1777281039 30
1777281044 30
1777281049 30
1777281054 30
1777281059 30
1777281064 30
1777281069 30
1777281074 30
1777281079 30
```
</details>

---

