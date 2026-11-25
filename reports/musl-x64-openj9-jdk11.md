---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:28:14 EST

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
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 91-94 cores)</summary>

```
1795641757 91
1795641762 94
1795641767 94
1795641772 94
1795641777 94
1795641782 94
1795641787 94
1795641792 94
1795641797 94
1795641802 92
1795641807 92
1795641812 92
1795641817 92
1795641822 92
1795641827 92
1795641832 92
1795641837 94
1795641842 94
1795641847 92
1795641852 92
```
</details>

---

