---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 18-22 cores)</summary>

```
1790172165 18
1790172170 18
1790172175 18
1790172180 18
1790172185 18
1790172190 18
1790172195 18
1790172200 20
1790172205 20
1790172210 22
1790172215 22
1790172220 22
1790172225 22
1790172230 22
1790172235 22
1790172240 22
1790172245 22
1790172250 22
1790172255 22
1790172260 22
```
</details>

---

