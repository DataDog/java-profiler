---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 07:23:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1793359113 57
1793359118 57
1793359123 57
1793359128 57
1793359133 57
1793359138 59
1793359143 59
1793359148 59
1793359153 59
1793359158 59
1793359163 59
1793359168 59
1793359173 59
1793359178 59
1793359183 59
1793359188 59
1793359193 59
1793359198 59
1793359203 59
1793359208 59
```
</details>

---

