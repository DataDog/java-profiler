---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 12:05:52 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1791475169 93
1791475174 93
1791475179 93
1791475184 93
1791475189 96
1791475194 96
1791475199 96
1791475204 96
1791475209 96
1791475214 96
1791475219 96
1791475224 96
1791475229 96
1791475234 96
1791475239 96
1791475244 96
1791475249 96
1791475254 96
1791475259 88
1791475264 88
```
</details>

---

