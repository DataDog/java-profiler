---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 08:01:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1794920148 72
1794920153 72
1794920158 72
1794920163 72
1794920168 72
1794920173 72
1794920178 72
1794920183 72
1794920188 72
1794920193 72
1794920198 72
1794920203 72
1794920208 72
1794920213 70
1794920218 70
1794920223 72
1794920228 72
1794920233 72
1794920238 72
1794920243 72
```
</details>

---

