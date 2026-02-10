---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-10 07:11:29 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1028 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1770725150 27
1770725155 27
1770725160 27
1770725165 27
1770725170 27
1770725175 27
1770725180 27
1770725185 27
1770725190 27
1770725195 27
1770725200 27
1770725205 27
1770725210 27
1770725215 27
1770725220 27
1770725225 25
1770725230 25
1770725235 25
1770725240 25
1770725245 25
```
</details>

---

