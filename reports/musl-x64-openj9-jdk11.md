---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 18:48:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 597 |

<details>
<summary>CPU Timeline (3 unique values: 87-96 cores)</summary>

```
1794267753 91
1794267758 91
1794267763 91
1794267768 91
1794267773 91
1794267778 91
1794267783 91
1794267788 91
1794267793 91
1794267798 91
1794267803 96
1794267808 96
1794267813 96
1794267818 87
1794267823 87
1794267828 87
1794267833 87
1794267838 87
1794267843 87
1794267848 87
```
</details>

---

