---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 00:07:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 71-79 cores)</summary>

```
1794546143 71
1794546148 71
1794546153 71
1794546158 71
1794546163 79
1794546168 79
1794546173 79
1794546178 79
1794546183 79
1794546188 79
1794546193 79
1794546198 79
1794546203 79
1794546208 79
1794546213 79
1794546218 79
1794546223 79
1794546228 79
1794546233 79
1794546238 79
```
</details>

---

