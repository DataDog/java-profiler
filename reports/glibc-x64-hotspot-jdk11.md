---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 14:11:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 52-62 cores)</summary>

```
1793819171 56
1793819176 54
1793819181 54
1793819186 54
1793819191 54
1793819196 54
1793819201 52
1793819206 52
1793819211 52
1793819216 52
1793819221 52
1793819226 52
1793819231 52
1793819236 52
1793819241 57
1793819246 57
1793819251 62
1793819256 62
1793819261 62
1793819266 62
```
</details>

---

