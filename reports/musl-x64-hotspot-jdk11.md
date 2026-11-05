---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:10 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1793890187 43
1793890192 43
1793890197 43
1793890202 43
1793890207 43
1793890212 43
1793890217 43
1793890222 43
1793890227 43
1793890232 43
1793890237 46
1793890242 46
1793890247 46
1793890252 46
1793890257 46
1793890263 46
1793890268 46
1793890273 46
1793890278 46
1793890283 46
```
</details>

---

