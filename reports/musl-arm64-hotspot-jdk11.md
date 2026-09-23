---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 12:35:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 6 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 13 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 30-46 cores)</summary>

```
1790181034 30
1790181039 30
1790181044 30
1790181049 46
1790181054 46
1790181059 46
1790181064 46
1790181069 46
1790181074 46
1790181079 46
1790181084 46
1790181089 46
1790181094 46
1790181099 46
1790181104 46
1790181109 41
1790181114 41
1790181119 41
1790181124 41
1790181129 41
```
</details>

---

