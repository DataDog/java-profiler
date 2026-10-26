---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 06:58:46 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 37-44 cores)</summary>

```
1793011772 44
1793011777 44
1793011782 44
1793011787 44
1793011792 44
1793011797 44
1793011802 44
1793011807 44
1793011812 44
1793011817 44
1793011822 44
1793011827 44
1793011832 44
1793011837 44
1793011842 44
1793011847 44
1793011852 40
1793011857 40
1793011862 40
1793011867 40
```
</details>

---

