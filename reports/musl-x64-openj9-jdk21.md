---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 14.90/sec |
| Health Score | 931% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 22.17/sec |
| Health Score | 1386% |
| Threads | 12 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 68-73 cores)</summary>

```
1769702712 68
1769702717 68
1769702722 68
1769702727 68
1769702732 68
1769702737 70
1769702742 70
1769702747 70
1769702752 70
1769702757 70
1769702762 70
1769702767 70
1769702772 70
1769702777 70
1769702782 70
1769702787 70
1769702792 73
1769702797 73
1769702802 73
1769702807 73
```
</details>

---

