---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 16:37:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 897 |
| Sample Rate | 14.95/sec |
| Health Score | 934% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1792614696 96
1792614701 96
1792614706 96
1792614711 96
1792614716 96
1792614721 96
1792614726 96
1792614731 96
1792614736 96
1792614741 96
1792614746 88
1792614751 88
1792614756 88
1792614761 88
1792614766 88
1792614771 88
1792614776 88
1792614781 88
1792614786 88
1792614791 88
```
</details>

---

