---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 06:58:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793011792 39
1793011797 39
1793011802 39
1793011807 39
1793011812 39
1793011817 39
1793011822 39
1793011827 39
1793011832 39
1793011837 39
1793011842 39
1793011847 39
1793011852 39
1793011857 39
1793011862 39
1793011867 39
1793011872 39
1793011877 39
1793011882 39
1793011887 39
```
</details>

---

