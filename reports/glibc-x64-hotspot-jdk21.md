---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 57-86 cores)</summary>

```
1790094008 86
1790094013 86
1790094018 86
1790094023 86
1790094028 77
1790094033 77
1790094038 77
1790094043 77
1790094048 77
1790094053 77
1790094058 77
1790094063 77
1790094068 77
1790094073 77
1790094078 77
1790094083 57
1790094088 57
1790094093 57
1790094098 57
1790094103 57
```
</details>

---

