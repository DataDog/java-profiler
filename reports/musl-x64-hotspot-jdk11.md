---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 28-32 cores)</summary>

```
1777280984 28
1777280989 28
1777280994 28
1777280999 28
1777281004 28
1777281009 30
1777281014 30
1777281019 30
1777281024 30
1777281029 30
1777281034 30
1777281039 30
1777281044 30
1777281049 32
1777281054 32
1777281059 32
1777281064 32
1777281069 32
1777281074 32
1777281079 32
```
</details>

---

