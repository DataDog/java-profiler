---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793734764 48
1793734769 48
1793734774 48
1793734779 48
1793734784 48
1793734789 48
1793734794 48
1793734799 48
1793734804 48
1793734809 48
1793734814 48
1793734819 48
1793734824 48
1793734829 48
1793734834 48
1793734839 48
1793734844 48
1793734849 48
1793734854 48
1793734859 48
```
</details>

---

