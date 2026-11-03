---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1793721191 59
1793721196 59
1793721201 59
1793721206 59
1793721211 59
1793721216 59
1793721221 59
1793721226 59
1793721231 59
1793721236 59
1793721241 59
1793721246 59
1793721251 59
1793721256 59
1793721261 61
1793721266 61
1793721271 61
1793721276 61
1793721281 61
1793721286 61
```
</details>

---

