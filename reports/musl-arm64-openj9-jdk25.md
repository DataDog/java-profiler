---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:08:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 12-48 cores)</summary>

```
1789995766 12
1789995771 12
1789995776 12
1789995781 12
1789995786 12
1789995791 12
1789995796 12
1789995801 12
1789995806 12
1789995811 12
1789995816 12
1789995821 12
1789995826 12
1789995831 12
1789995836 12
1789995841 12
1789995846 12
1789995851 12
1789995856 12
1789995861 12
```
</details>

---

