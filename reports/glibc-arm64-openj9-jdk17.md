---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 9 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1789995787 48
1789995792 36
1789995797 36
1789995802 36
1789995807 36
1789995812 36
1789995817 36
1789995822 36
1789995827 36
1789995832 36
1789995837 36
1789995842 36
1789995848 36
1789995853 36
1789995858 36
1789995863 36
1789995868 36
1789995873 36
1789995878 36
1789995883 36
```
</details>

---

