---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 00:07:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794546136 63
1794546141 63
1794546146 63
1794546151 63
1794546156 63
1794546161 63
1794546166 63
1794546171 63
1794546176 63
1794546181 63
1794546186 63
1794546191 59
1794546196 59
1794546201 59
1794546206 59
1794546211 59
1794546216 59
1794546221 61
1794546226 61
1794546231 61
```
</details>

---

