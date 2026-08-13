---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 05:46:09 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1786614122 41
1786614127 41
1786614132 41
1786614137 41
1786614142 41
1786614147 41
1786614152 52
1786614157 52
1786614162 52
1786614167 52
1786614172 52
1786614177 52
1786614182 52
1786614187 52
1786614192 54
1786614197 54
1786614202 54
1786614207 54
1786614212 54
1786614217 54
```
</details>

---

