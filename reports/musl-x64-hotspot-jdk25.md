---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 00:56:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 32-72 cores)</summary>

```
1790052742 32
1790052747 32
1790052752 32
1790052757 32
1790052762 32
1790052767 32
1790052772 32
1790052777 32
1790052782 34
1790052787 34
1790052792 34
1790052797 34
1790052802 34
1790052807 34
1790052812 34
1790052817 72
1790052822 72
1790052827 39
1790052832 39
1790052837 39
```
</details>

---

