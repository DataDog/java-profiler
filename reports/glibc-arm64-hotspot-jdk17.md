---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 05:26:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787044761 32
1787044766 32
1787044771 32
1787044776 32
1787044781 32
1787044786 32
1787044791 32
1787044796 32
1787044801 32
1787044806 32
1787044811 32
1787044816 32
1787044821 32
1787044826 32
1787044831 32
1787044836 32
1787044841 32
1787044846 32
1787044851 32
1787044856 32
```
</details>

---

