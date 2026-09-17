---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:41:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1789673461 92
1789673466 92
1789673471 92
1789673476 92
1789673481 92
1789673486 90
1789673491 90
1789673497 90
1789673502 90
1789673507 90
1789673512 92
1789673517 92
1789673522 92
1789673527 94
1789673532 94
1789673537 94
1789673542 94
1789673547 94
1789673552 94
1789673557 94
```
</details>

---

