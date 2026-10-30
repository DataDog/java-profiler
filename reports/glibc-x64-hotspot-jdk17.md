---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:23:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 9-32 cores)</summary>

```
1793373501 9
1793373506 9
1793373511 9
1793373516 9
1793373521 9
1793373526 9
1793373531 9
1793373536 9
1793373541 9
1793373546 9
1793373551 9
1793373556 29
1793373561 29
1793373566 29
1793373571 29
1793373576 29
1793373581 29
1793373586 29
1793373591 29
1793373596 29
```
</details>

---

