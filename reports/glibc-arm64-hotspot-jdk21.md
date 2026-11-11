---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 07:51:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1794401185 36
1794401190 36
1794401195 36
1794401200 36
1794401205 36
1794401210 36
1794401215 36
1794401220 36
1794401225 36
1794401230 36
1794401235 36
1794401240 36
1794401245 36
1794401250 36
1794401255 36
1794401260 36
1794401265 36
1794401270 36
1794401275 36
1794401280 48
```
</details>

---

