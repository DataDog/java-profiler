---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:26:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787044736 64
1787044741 64
1787044746 64
1787044751 64
1787044756 64
1787044761 64
1787044766 64
1787044771 64
1787044776 64
1787044781 64
1787044786 64
1787044791 64
1787044796 64
1787044801 64
1787044806 64
1787044811 64
1787044816 64
1787044821 64
1787044826 64
1787044831 64
```
</details>

---

