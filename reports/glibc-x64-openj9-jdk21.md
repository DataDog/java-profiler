---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 05:49:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (2 unique values: 33-61 cores)</summary>

```
1788342296 61
1788342301 61
1788342306 61
1788342311 61
1788342316 61
1788342321 33
1788342326 33
1788342331 33
1788342336 33
1788342341 33
1788342346 33
1788342351 33
1788342356 33
1788342361 33
1788342366 33
1788342371 33
1788342376 33
1788342381 33
1788342386 33
1788342391 33
```
</details>

---

