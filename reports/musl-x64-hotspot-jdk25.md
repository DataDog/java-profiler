---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:38 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 35-41 cores)</summary>

```
1794546174 35
1794546179 35
1794546184 35
1794546189 35
1794546194 35
1794546199 35
1794546204 35
1794546209 35
1794546214 35
1794546219 39
1794546224 39
1794546229 39
1794546234 39
1794546239 41
1794546244 41
1794546249 39
1794546254 39
1794546259 39
1794546264 39
1794546269 39
```
</details>

---

