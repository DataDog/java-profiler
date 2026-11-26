---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1795706138 92
1795706143 92
1795706148 92
1795706153 94
1795706158 94
1795706163 94
1795706168 94
1795706173 94
1795706178 94
1795706183 94
1795706188 94
1795706193 94
1795706198 94
1795706203 94
1795706208 94
1795706213 94
1795706218 94
1795706223 94
1795706228 94
1795706233 96
```
</details>

---

