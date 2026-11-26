---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:21:26 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1795706155 28
1795706160 28
1795706165 28
1795706170 28
1795706175 28
1795706180 28
1795706185 28
1795706190 28
1795706195 30
1795706200 30
1795706205 30
1795706210 30
1795706215 30
1795706220 30
1795706225 30
1795706230 30
1795706235 30
1795706240 30
1795706245 30
1795706250 30
```
</details>

---

