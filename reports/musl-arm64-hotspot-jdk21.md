---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 06:28:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 13-18 cores)</summary>

```
1793355787 15
1793355792 15
1793355797 15
1793355802 15
1793355807 18
1793355812 18
1793355817 13
1793355822 13
1793355827 13
1793355832 13
1793355837 13
1793355842 13
1793355847 13
1793355852 13
1793355857 13
1793355862 13
1793355867 13
1793355872 13
1793355877 13
1793355882 13
```
</details>

---

