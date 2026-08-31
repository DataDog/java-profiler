---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-31 11:44:50 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 10 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1788190778 22
1788190783 22
1788190788 22
1788190793 22
1788190798 22
1788190803 22
1788190808 22
1788190813 22
1788190818 22
1788190823 22
1788190828 22
1788190833 22
1788190838 22
1788190843 22
1788190848 22
1788190853 20
1788190858 20
1788190863 20
1788190868 20
1788190873 20
```
</details>

---

