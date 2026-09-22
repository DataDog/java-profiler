---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 53-62 cores)</summary>

```
1790093998 62
1790094003 53
1790094008 53
1790094013 53
1790094018 53
1790094023 53
1790094028 53
1790094033 53
1790094038 53
1790094043 53
1790094048 53
1790094053 53
1790094058 53
1790094063 53
1790094068 53
1790094073 53
1790094078 53
1790094083 55
1790094088 55
1790094093 55
```
</details>

---

