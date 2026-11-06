---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 09:29:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793975064 46
1793975069 46
1793975074 46
1793975079 46
1793975084 46
1793975089 46
1793975094 46
1793975099 46
1793975104 46
1793975109 46
1793975114 46
1793975119 46
1793975124 46
1793975129 46
1793975134 46
1793975139 46
1793975144 46
1793975149 48
1793975154 48
1793975159 48
```
</details>

---

