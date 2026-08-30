---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-30 05:49:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1788083165 32
1788083170 32
1788083175 32
1788083180 32
1788083185 32
1788083190 32
1788083195 32
1788083200 32
1788083205 32
1788083210 32
1788083216 32
1788083221 27
1788083226 27
1788083231 27
1788083236 27
1788083241 27
1788083246 27
1788083251 27
1788083256 27
1788083261 27
```
</details>

---

