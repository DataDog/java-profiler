---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 16:33:57 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 11 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1777321783 59
1777321788 59
1777321793 47
1777321798 47
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
```
</details>

---

