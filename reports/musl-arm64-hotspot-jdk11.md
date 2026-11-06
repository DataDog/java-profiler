---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 09:29:17 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 36-48 cores)</summary>

```
1793975095 48
1793975100 48
1793975105 43
1793975110 43
1793975115 43
1793975120 43
1793975125 43
1793975130 43
1793975135 43
1793975140 43
1793975145 43
1793975150 43
1793975155 42
1793975160 42
1793975165 42
1793975170 42
1793975175 42
1793975180 42
1793975185 42
1793975190 42
```
</details>

---

