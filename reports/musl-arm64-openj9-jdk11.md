---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 09:37:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1788528776 64
1788528781 44
1788528786 44
1788528791 44
1788528796 44
1788528801 44
1788528806 44
1788528811 44
1788528816 44
1788528821 44
1788528826 44
1788528831 44
1788528836 44
1788528841 44
1788528846 44
1788528851 44
1788528856 44
1788528861 44
1788528866 44
1788528871 44
```
</details>

---

