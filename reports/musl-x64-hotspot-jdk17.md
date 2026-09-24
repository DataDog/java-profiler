---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 11:09:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1790262019 27
1790262024 27
1790262029 27
1790262034 27
1790262039 27
1790262044 27
1790262049 27
1790262054 27
1790262059 27
1790262064 25
1790262069 25
1790262074 25
1790262079 25
1790262084 25
1790262089 25
1790262094 25
1790262099 25
1790262104 25
1790262109 25
1790262114 25
```
</details>

---

