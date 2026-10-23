---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-23 05:55:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 52-76 cores)</summary>

```
1792749024 65
1792749029 65
1792749034 65
1792749039 65
1792749044 65
1792749049 65
1792749054 65
1792749059 76
1792749064 76
1792749069 76
1792749074 76
1792749079 52
1792749084 52
1792749089 52
1792749094 52
1792749099 52
1792749104 52
1792749109 72
1792749114 72
1792749119 72
```
</details>

---

