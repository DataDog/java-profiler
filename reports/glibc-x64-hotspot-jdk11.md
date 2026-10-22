---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 06:46:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1792665776 93
1792665781 93
1792665786 93
1792665791 93
1792665796 93
1792665801 93
1792665806 93
1792665811 93
1792665816 93
1792665821 93
1792665826 93
1792665831 93
1792665836 93
1792665841 93
1792665846 91
1792665851 91
1792665856 91
1792665861 91
1792665866 91
1792665871 91
```
</details>

---

