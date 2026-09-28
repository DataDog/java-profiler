---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 10:34:15 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 10 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 35-64 cores)</summary>

```
1790605762 59
1790605767 59
1790605772 59
1790605777 59
1790605782 64
1790605787 64
1790605792 63
1790605797 63
1790605802 63
1790605807 63
1790605812 63
1790605817 63
1790605822 63
1790605827 63
1790605832 63
1790605837 63
1790605842 63
1790605847 63
1790605852 63
1790605857 63
```
</details>

---

