---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 11:27:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 19-43 cores)</summary>

```
1792596159 23
1792596164 23
1792596169 23
1792596174 23
1792596179 23
1792596184 23
1792596189 23
1792596194 23
1792596199 23
1792596204 23
1792596209 23
1792596214 23
1792596219 23
1792596224 23
1792596229 23
1792596234 43
1792596239 43
1792596244 19
1792596249 19
1792596254 19
```
</details>

---

