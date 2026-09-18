---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 04:34:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 69-74 cores)</summary>

```
1789719878 69
1789719883 69
1789719888 69
1789719893 74
1789719898 74
1789719903 74
1789719908 74
1789719913 74
1789719918 74
1789719923 74
1789719928 74
1789719933 74
1789719938 74
1789719943 74
1789719948 74
1789719953 74
1789719958 74
1789719963 74
1789719968 74
1789719973 74
```
</details>

---

