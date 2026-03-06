---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-06 04:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 11-20 cores)</summary>

```
1772790191 18
1772790196 18
1772790201 20
1772790206 20
1772790211 20
1772790216 20
1772790221 20
1772790226 20
1772790231 20
1772790236 20
1772790241 20
1772790246 20
1772790251 20
1772790256 20
1772790261 20
1772790266 20
1772790271 20
1772790276 20
1772790281 20
1772790286 20
```
</details>

---

