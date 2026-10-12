---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 23:04:59 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 11 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1791774059 16
1791774064 16
1791774069 16
1791774074 16
1791774079 16
1791774084 16
1791774089 16
1791774094 16
1791774099 16
1791774104 16
1791774109 16
1791774114 16
1791774119 16
1791774124 16
1791774129 16
1791774134 16
1791774139 16
1791774144 16
1791774149 16
1791774154 16
```
</details>

---

