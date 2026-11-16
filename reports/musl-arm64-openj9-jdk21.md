---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 08:52:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794836780 46
1794836785 46
1794836790 46
1794836795 46
1794836800 46
1794836805 46
1794836810 46
1794836815 46
1794836820 46
1794836826 46
1794836831 46
1794836836 46
1794836841 46
1794836846 46
1794836851 48
1794836856 48
1794836861 48
1794836866 48
1794836871 48
1794836876 48
```
</details>

---

