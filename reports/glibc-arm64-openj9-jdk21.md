---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 12:01:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 14 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (5 unique values: 25-33 cores)</summary>

```
1793897782 32
1793897787 32
1793897792 32
1793897797 32
1793897802 32
1793897807 32
1793897812 32
1793897817 33
1793897822 33
1793897827 33
1793897832 33
1793897837 33
1793897842 33
1793897847 28
1793897852 28
1793897857 28
1793897862 28
1793897867 28
1793897872 28
1793897877 28
```
</details>

---

