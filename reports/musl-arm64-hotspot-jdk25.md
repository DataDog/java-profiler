---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-09 05:04:59 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1775724977 59
1775724982 59
1775724987 59
1775724992 59
1775724997 64
1775725002 64
1775725007 64
1775725012 64
1775725017 64
1775725022 64
1775725027 64
1775725032 64
1775725037 64
1775725042 64
1775725047 64
1775725052 64
1775725057 64
1775725062 64
1775725067 64
1775725072 64
```
</details>

---

