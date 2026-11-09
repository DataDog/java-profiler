---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 10:36:32 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 12 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794238194 40
1794238199 40
1794238204 35
1794238209 35
1794238214 35
1794238219 35
1794238224 35
1794238229 35
1794238234 35
1794238239 35
1794238244 35
1794238249 35
1794238254 35
1794238259 35
1794238264 40
1794238269 40
1794238274 40
1794238279 40
1794238284 40
1794238289 40
```
</details>

---

