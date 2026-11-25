---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:01:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795607802 64
1795607807 64
1795607812 64
1795607817 64
1795607822 64
1795607827 64
1795607832 64
1795607837 64
1795607842 64
1795607847 64
1795607852 64
1795607857 64
1795607862 64
1795607867 64
1795607872 64
1795607877 64
1795607882 64
1795607887 64
1795607892 64
1795607897 64
```
</details>

---

