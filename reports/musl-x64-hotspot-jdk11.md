---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 19:20:35 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 19-46 cores)</summary>

```
1793924164 46
1793924169 46
1793924174 46
1793924179 46
1793924184 46
1793924189 46
1793924194 21
1793924199 21
1793924204 19
1793924210 19
1793924215 19
1793924220 19
1793924225 19
1793924230 19
1793924235 19
1793924240 19
1793924245 19
1793924250 19
1793924255 19
1793924260 19
```
</details>

---

