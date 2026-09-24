---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 00:59:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790225654 50
1790225659 50
1790225664 50
1790225669 50
1790225674 50
1790225679 50
1790225684 50
1790225689 50
1790225694 50
1790225699 50
1790225704 50
1790225709 50
1790225714 50
1790225719 50
1790225724 50
1790225729 50
1790225734 50
1790225739 50
1790225744 50
1790225749 50
```
</details>

---

