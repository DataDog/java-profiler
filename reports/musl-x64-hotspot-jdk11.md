---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 07:53:27 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 45-54 cores)</summary>

```
1770122792 54
1770122797 54
1770122802 54
1770122807 54
1770122812 54
1770122817 54
1770122822 54
1770122827 54
1770122832 54
1770122837 54
1770122842 48
1770122847 48
1770122852 48
1770122857 50
1770122862 50
1770122867 50
1770122872 50
1770122877 45
1770122882 45
1770122887 45
```
</details>

---

