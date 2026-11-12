---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:27:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1794504170 22
1794504175 22
1794504180 22
1794504185 22
1794504190 22
1794504195 22
1794504200 22
1794504205 27
1794504210 27
1794504215 27
1794504220 27
1794504225 27
1794504230 27
1794504235 27
1794504240 22
1794504245 22
1794504250 22
1794504255 22
1794504260 22
1794504265 22
```
</details>

---

