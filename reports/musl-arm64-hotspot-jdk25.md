---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 16:51:01 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793742169 30
1793742174 30
1793742179 30
1793742184 30
1793742189 30
1793742194 30
1793742199 30
1793742204 30
1793742209 30
1793742214 30
1793742219 30
1793742224 30
1793742229 30
1793742234 30
1793742239 30
1793742244 30
1793742249 30
1793742254 30
1793742259 30
1793742264 30
```
</details>

---

