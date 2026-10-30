---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:38:18 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 13-30 cores)</summary>

```
1793367159 13
1793367164 13
1793367169 13
1793367174 13
1793367179 13
1793367184 13
1793367189 13
1793367194 13
1793367199 13
1793367204 13
1793367209 13
1793367214 30
1793367219 30
1793367224 30
1793367229 30
1793367234 30
1793367239 30
1793367244 30
1793367249 30
1793367254 30
```
</details>

---

