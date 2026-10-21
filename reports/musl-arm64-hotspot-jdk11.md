---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 05:55:33 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 52-53 cores)</summary>

```
1792576242 52
1792576247 52
1792576252 52
1792576257 52
1792576262 52
1792576267 53
1792576272 53
1792576278 53
1792576283 53
1792576288 53
1792576293 53
1792576298 53
1792576303 53
1792576308 53
1792576313 53
1792576318 53
1792576323 53
1792576328 53
1792576333 53
1792576338 53
```
</details>

---

