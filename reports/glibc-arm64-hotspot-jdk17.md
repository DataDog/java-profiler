---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 16:33:57 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777321788 64
1777321793 64
1777321798 64
1777321803 64
1777321808 64
1777321813 64
1777321818 64
1777321823 64
1777321828 64
1777321833 64
1777321838 64
1777321843 64
1777321848 64
1777321853 64
1777321858 64
1777321863 64
1777321868 64
1777321873 64
1777321878 64
1777321883 64
```
</details>

---

