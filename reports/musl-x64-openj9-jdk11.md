---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 74-96 cores)</summary>

```
1789682158 76
1789682163 76
1789682168 74
1789682173 74
1789682178 74
1789682183 74
1789682188 74
1789682193 74
1789682198 74
1789682203 74
1789682208 74
1789682213 74
1789682218 94
1789682223 94
1789682228 94
1789682233 94
1789682238 94
1789682243 94
1789682248 96
1789682253 96
```
</details>

---

