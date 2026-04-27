---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:08 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777280989 64
1777280994 64
1777280999 64
1777281004 64
1777281009 64
1777281014 64
1777281019 64
1777281024 64
1777281029 64
1777281034 64
1777281039 64
1777281044 64
1777281049 64
1777281054 64
1777281059 64
1777281064 64
1777281069 64
1777281074 64
1777281079 64
1777281084 64
```
</details>

---

