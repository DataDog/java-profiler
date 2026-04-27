---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777280998 59
1777281003 59
1777281009 59
1777281014 59
1777281019 59
1777281024 59
1777281029 59
1777281034 59
1777281039 59
1777281044 59
1777281049 59
1777281054 64
1777281059 64
1777281064 64
1777281069 64
1777281074 64
1777281079 64
1777281084 64
1777281089 64
1777281094 64
```
</details>

---

