---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 22.43/sec |
| Health Score | 1402% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 28.80/sec |
| Health Score | 1800% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 42-62 cores)</summary>

```
1769697751 42
1769697756 42
1769697761 42
1769697766 42
1769697771 42
1769697776 42
1769697781 42
1769697786 42
1769697791 42
1769697796 42
1769697801 42
1769697806 42
1769697811 62
1769697816 62
1769697821 62
1769697826 62
1769697831 62
1769697836 62
1769697841 62
1769697846 62
```
</details>

---

