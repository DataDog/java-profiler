---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 10:58:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787151284 43
1787151289 43
1787151294 43
1787151299 43
1787151304 43
1787151309 43
1787151314 43
1787151319 43
1787151324 43
1787151329 43
1787151334 43
1787151339 43
1787151344 43
1787151349 43
1787151354 48
1787151359 48
1787151364 48
1787151369 48
1787151374 48
1787151379 48
```
</details>

---

