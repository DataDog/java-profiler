---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 16:50:59 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (6 unique values: 40-47 cores)</summary>

```
1793742170 44
1793742175 44
1793742180 44
1793742185 44
1793742190 44
1793742195 44
1793742200 44
1793742205 44
1793742210 44
1793742215 44
1793742220 44
1793742225 44
1793742230 44
1793742235 46
1793742240 46
1793742245 47
1793742250 47
1793742255 42
1793742260 42
1793742265 40
```
</details>

---

