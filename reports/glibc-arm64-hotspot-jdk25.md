---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794546212 24
1794546217 24
1794546222 24
1794546227 24
1794546232 24
1794546237 24
1794546242 24
1794546247 24
1794546252 29
1794546257 29
1794546262 34
1794546267 34
1794546272 34
1794546277 34
1794546282 34
1794546287 34
1794546292 34
1794546297 34
1794546302 34
1794546307 34
```
</details>

---

