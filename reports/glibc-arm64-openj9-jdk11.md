---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 10:04:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777384752 64
1777384757 64
1777384762 64
1777384767 64
1777384772 64
1777384777 64
1777384782 64
1777384787 64
1777384792 64
1777384797 64
1777384802 64
1777384807 64
1777384812 64
1777384817 64
1777384822 64
1777384827 64
1777384832 64
1777384837 64
1777384842 64
1777384847 64
```
</details>

---

