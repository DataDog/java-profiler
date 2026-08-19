---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 10:58:57 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787151254 88
1787151259 88
1787151264 88
1787151269 88
1787151274 88
1787151279 88
1787151284 88
1787151289 88
1787151294 88
1787151299 88
1787151304 96
1787151309 96
1787151314 96
1787151319 96
1787151324 96
1787151329 96
1787151335 96
1787151340 96
1787151345 96
1787151350 96
```
</details>

---

